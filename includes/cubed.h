/* ************************************************************************** */
/*															 */
/*											 :::	 ::::::::   */
/*   cubed.h									:+:	 :+:	:+:   */
/*										  +:+ +:+		+:+	*/
/*   By: leoherna <marvin@42.fr>				+#+  +:+	  +#+	   */
/*									   +#+#+#+#+#+   +#+		 */
/*   Created: 2024/04/16 15:03:08 by arpages		 #+#	#+#		   */
/*   Updated: 2024/04/23 13:53:17 by leoherna		###   ########.fr	  */
/*															 */
/* ************************************************************************** */

#ifndef CUBED_H
# define CUBED_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <sys/time.h>

# include "get_next_line.h"
# include "../minilibx/mlx.h"

# include "struct.h"

# define TEX_SIZE 256

/*------srcs/main/game_manager------*/
int     game_manager(t_data *data);
void	move_player(t_data *data, int x, int y);
void	rotate_player(t_data *data, double angle);
int		multi_key(t_data *data);
void	generate_base_img(t_data *data);

void	jump(t_data *data);

/*------srcs/main/init-----*/
void	get_all(char **argv, t_data *data);
void	copy_file(t_map_info *map_info);
void	get_map(t_map_info *map_info);
int		is_map_part(char *line);
void	set_pos(t_data *data, int x, int y, char dir);
void	set_keys(t_data *data);
void	set_vector(t_data *data, int x, int y);

/*------srcs/main/checker.c-----*/
int		check_map(t_data *data);
int		check_file(char *str);

/*------srcs/map/map_checker*/
int		check_walls(t_data *data);
int		check_walls_bis(t_data *data, int x, int y);

/*------srcs/main/error.c-----*/
void	error_manager(char *line, int code);

/*------srcs/raycasting/raycasting.c---*/
void	send_rays(t_data *data);
void	one_ray(t_data *data, double rdX, double rdY, int x);
void	calculate_init_dist(t_data *data, t_raystate *raystate, double rdx, double rdy);
void	ray_loop(t_data *data, t_raystate *raystate);
void	get_line_data(t_data *data, t_raystate *raystate);

void    pixel_put_opti(t_img *img, int x, int y, int color);
void	drawVerticalLine(t_data *data, t_raystate *raystate, int yMin, int yMax, t_img *img);
void	clearScreen(t_img *img, int width, int height);

void	reajust_line(t_data *data, int *l_start, int *l_end);

/*------srcs/utils/free_manager----- */
void    free_mapinfo(t_data *data);
void    free_tab(char **tab);

/*------srcs/utils/tools*/
void	print_tab(char **tab);
char	**tab_realloc(char **tab, int m_size, char *content);
int		tab_size(char **tab);
size_t	get_current_time(void);

//------srcs/utils/ft_itoa.c*/
char	*ft_itoa(int n);

/*------srcs/utils/ft_tools.c*/
int		ft_strlen(char *str);
int		ft_strchr(char c, char *str);
int		ft_strncmp(const char *str1, const char *str2, unsigned int n);
char	*ft_strdup(char *s);

int		get_pixel_color(t_img *img, int x, int y);

int		assombrirCouleur(int couleurOriginale, int assombrissement);

void	get_image(t_data *data);
void	create_image(t_data *data);

int		get_smoothed_color(t_img *img, int color, double power);
int		blend_color(t_img *img);

#endif
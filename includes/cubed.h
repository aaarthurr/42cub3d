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
# include <sys/time.h>
# include <time.h>
# include "../minilibx/mlx.h"

# include "struct.h"

# define TEX_SIZE 256
# define SPRITE_SIZE 128
# define ACTIVATE_MOUSE 1

/*------srcs/main/game_manager------*/
int		game_manager(t_data *data);
int		multi_key(t_data *data);
void	generate_base_img(t_data *data);
int		close_window(t_data *data);

/*------srcs/main/move------*/
void	move_player(t_data *data, int x, int y);
void	rotate_player(t_data *data, double angle);
void	jump(t_data *data);
void	walk_height(t_data *data);
int		mouse_move(int x, int y, t_data *data);

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
int		check_elements(t_data *data);
int		path_finding(t_data *data);
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
void	pixel_put_opti(t_img *img, int x, int y, int color);
void	drawVerticalLine(t_data *data, t_raystate *raystate, int yMin, int yMax, t_img *img);
void	clearScreen(t_img *img, int width, int height);
void	reajust_line(t_data *data, t_raystate *raystate, int *l_start, int *l_end);

/*------srcs/raycasting/roof_Cast.c---*/
void	cast_floor(t_data *data);

/*------srcs/raycasting/texture.c---*/
char	*generate_path(t_data *data, int index, char *which_texture);
char	*find_arg(t_data *data, char *which_texture);

/*------srcs/raycasting/get_floor.c---*/
int		search_floor_color(t_data *data);
int		search_ceiling_color(t_data *data);

/*------srcs/utils/free_manager----- */
void	free_function(t_data *data);
void	free_line(t_data *data);
void	exit_manager(t_data *data);

/*------srcs/utils/tools*/
void	print_tab(char **tab);
int		tab_size(char **tab);
size_t	get_current_time(void);
char	*ft_strdup(char *src);

/*------srcs/utils/tools_bis*/
void	free_tab(char **tab);
int		ft_atoi(const char *nptr);
int		ft_isdigit(int c);

//------srcs/utils/ft_itoa.c*/
char	*ft_itoa(int n);

/*------srcs/utils/ft_tools.c*/
int		ft_strchr(char c, char *str);
int		ft_strncmp(const char *str1, const char *str2, unsigned int n);
char	*ft_strdup(char *s);
int		get_pixel_color(t_img *img, int x, int y);
int		assombrirCouleur(int couleurOriginale, int assombrissement);
void	get_image(t_data *data);
void	create_image(t_data *data);
int		check_path(t_data *data);
int		give_lsd(t_data *date, int color);
void	print_map(t_data *data);
void	take_drugs(t_data *data);
void    death(t_data *data, const char *str);
void    set_sprite(t_data *data, int number);
void    cast_sprite(t_data *data);
void	give_effect(t_data *data);
int		is_odd(int x);
void	reajust_line_pills(t_data *data, t_spritestate *sp, int *l_start, int *l_end);

#endif
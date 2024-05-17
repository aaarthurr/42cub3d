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

# include "get_next_line.h"
#include "../minilibx/mlx.h"

typedef struct key_info_s
{
	int key_w;
	int key_a;
	int key_s;
	int key_d;
	int key_left;
	int key_right;
	int key_esc;
}			t_key_info;

typedef struct img_s
{
	void	*img_ptr;
	char	*img_char;
	int		bits_pix;
	int		endian;
	int		len;
}				t_img;


typedef struct map_info_s
{
	char *map_path;
	char **global;
	char **info;
	char **map;
	int height;
}			t_map_info;

typedef struct s_ray
{
	float x;
	float y;
		
}			t_ray;

typedef struct s_player
{
	//vecteur position
	double	posX;
	double	posY;
	//direction du joueur
	double	dirX;
	double	dirY;
	//plan de la camera
	double	planX;
	double	planY;

	int		speed;
}			t_player;

typedef struct data_s
{
	void		*mlx;
	void		*win;
	int			win_height;
	int			win_width;
	t_player	player;
	t_map_info  map_info;
	t_ray		ray;
	t_key_info	key_info;
	t_img		img;
}				t_data;


typedef struct raystate_s
{
	int		x;
	int		hit;
	int		side;
	int		mapX;
	int		mapY;
	int		stepX;
	int		stepY;
	double	sideDistX;
	double	sideDistY;
	double	deltaDistX;
	double	deltaDistY;
	double	perpWallDist;
}				t_raystate;

/*------srcs/main/game_manager------*/
int     game_manager(t_data *data);
void	move_player(t_data *data, int x, int y);
void	rotate_player(t_data *data, double angle);
int		multi_key(t_data *data);
void	generate_base_img(t_data *data);

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
void	draw_line_2(t_data *data, t_raystate *raystate, int x);

void    pixel_put_opti(t_img *img, int x, int y, int color);
void	drawVerticalLine(t_img *img, int x, int yMin, int yMax, int color, int height);
void	clearScreen(t_img *img, int width, int height);

/*------srcs/utils/free_manager----- */
void    free_mapinfo(t_data *data);
void    free_tab(char **tab);

/*------srcs/utils/tools*/
void	print_tab(char **tab);
char	**tab_realloc(char **tab, int m_size, char *content);
int		tab_size(char **tab);


/*--------srcs/utils/ft_tools.c*/
int		ft_strlen(char *str);
int		ft_strchr(char c, char *str);
int		ft_strncmp(const char *str1, const char *str2, unsigned int n);

#endif
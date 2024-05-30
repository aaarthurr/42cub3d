/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:04:51 by arthur            #+#    #+#             */
/*   Updated: 2024/05/30 13:21:15 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

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
	int		global_color;
}				t_img;


typedef struct map_info_s
{
	char *map_path;
	char **global;
	char **info;
	char **map;
	int height;
}			t_map_info;

typedef struct	texture_s
{
	t_img	wall;
}			t_texture;

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
	size_t		last_frame;
	t_player	player;
	t_map_info  map_info;
	t_key_info	key_info;
	t_img		img;
	t_texture	texture;
}				t_data;

typedef struct raystate_s
{
	double	rayDirX;
	double	rayDirY;
	int		x;
	int		hit;
	int		side;
	int		mapX;
	int		mapY;
	int		stepX;
	int		stepY;
	int		texX;
	int		line_height;
	double	wallX;
	double	sideDistX;
	double	sideDistY;
	double	deltaDistX;
	double	deltaDistY;
	double	perpWallDist;
}				t_raystate;

#endif
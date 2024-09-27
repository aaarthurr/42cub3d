/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leoherna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:04:51 by arthur            #+#    #+#             */
/*   Updated: 2024/09/28 14:53:21 by leoherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_pos
{
	int	x;
	int	y;
}				t_pos;

typedef struct s_actpos
{
	int	act_x;
	int	act_y;
}				t_actpos;
//pour path finding

typedef struct s_mouse
{
	int origin_x;
	int origin_y;
	int	mouse_lock;
} t_mouse;

typedef struct key_info_s
{
	int key_w;
	int key_a;
	int key_s;
	int key_d;
	int key_left;
	int key_right;
	int key_esc;
	int key_jump;
	int key_mouse;
	

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
	int	global_len;
	char **map;
	int height;

}			t_map_info;

typedef struct s_pills
{
    double        x;
    double        y;
    int            taken;
}            t_pills;

typedef    struct s_sprite
{
    int        number;
    double    *Zbuffer;
    t_pills    *pills;
}            t_sprite;

typedef struct s_spritestate
{
    double    spriteX;
    double    spriteY;
    double    invDet;
    double    transformX;
    double    transformY;
    int        spriteScreenX;
    int        spriteHeight;
    int        spriteWidth;
    int        drawStartY;
    int        drawEndY;
    int        drawStartX;
    int        drawEndX;
}            t_spritestate;

typedef struct	texture_s
{	
	t_img	Nwall;
	t_img	Swall;
	t_img	Wwall;
	t_img	Ewall;
	t_img	ceiling;
	t_img	pills;
	char	*Nwall_path;
	char	*Swall_path;
	char	*Wwall_path;
	char	*Ewall_path;
	char	*ceiling_path;
	
	unsigned int floor_color;
	unsigned int ceiling_color;
	int ceiling_color_or_texture;
	int r;
	int g;
	int b;
}			t_texture;

typedef struct s_player
{
	int			drug_level;
	long int	drug_time;
	// position en int
	int	IntposX;
	int	IntposY;
	//vecteur position
	double	posX;
	double	posY;
	double	posZ;
	//direction du joueur
	double	dirX;
	double	dirY;
	//plan de la camera
	double	planX;
	double	planY;

	int		walk_phase;

	int		is_falling;
	int		is_jumping;

	int		speed;
	double	jump_speed;

	int		base_dir;
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
	t_mouse		mouse;
	t_img		img;
	t_texture	texture;
	t_sprite	sprite;
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
	int		calculated_len;
	int		offset;
	double	wallX;
	double	sideDistX;
	double	sideDistY;
	double	deltaDistX;
	double	deltaDistY;
	double	perpWallDist;
}				t_raystate;

typedef struct roofstate_s
{
	int		x;
	int		y;
	float	rayDirX0;
	float	rayDirY0;
	float	rayDirX1;
	float	rayDirY1;
	int		p;
	float	floorStepX;
	float	floorStepY;
	float	floorX;
	float	floorY;
}			t_roofstate;

#endif
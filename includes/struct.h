/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arpages <arpages@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:04:51 by arthur            #+#    #+#             */
/*   Updated: 2024/09/30 15:23:32 by arpages          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_var
{
	int		a;
	int		b;
	int		c;
	int		i;
	int		j;
	int		k;
	int		o;
	int		x;
	int		y;
	int		z;
	int		top;
	int		fd;
	int		lstart;
	int		lend;
	int		size;
	int		nb_line;
	char	*temp;
	char	*str;
	char	**tab;
	double	d_a;
	double	d_b;
	double	d_c;
}			t_var;

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

typedef struct s_mouse
{
	int	origin_x;
	int	origin_y;
	int	mouse_lock;
}				t_mouse;

typedef struct key_info_s
{
	int	key_w;
	int	key_a;
	int	key_s;
	int	key_d;
	int	key_left;
	int	key_right;
	int	key_esc;
	int	key_jump;
	int	key_mouse;
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
	char	*map_path;
	char	**global;
	char	**map;
	int		global_len;
	int		height;

}			t_map_info;

typedef struct s_pills
{
	double		x;
	double		y;
	double		distance;
	int			index;
	int			taken;
}				t_pills;

typedef struct s_sprite
{
	int			number;
	double		*zbuffer;
	t_pills		*pills;
}				t_sprite;

typedef struct s_spritestate
{
	double	spritex;
	double	spritey;
	double	invdet;
	double	transformx;
	double	transformy;
	int		spritescreenx;
	int		spriteheight;
	int		spritewidth;
	int		drawstarty;
	int		drawendy;
	int		drawstartx;
	int		drawendx;
	int		offset;
	int		calculated_len;
}				t_spritestate;

typedef struct texture_s
{
	t_img			nwall;
	t_img			swall;
	t_img			wwall;
	t_img			ewall;
	t_img			ceiling;
	t_img			pills;
	char			*nwall_path;
	char			*swall_path;
	char			*wwall_path;
	char			*ewall_path;
	char			*ceiling_path;
	unsigned int	floor_color;
	unsigned int	ceiling_color;
	int				ceiling_color_or_texture;
	int				r;
	int				g;
	int				b;
}				t_texture;

typedef struct s_player
{
	int			drug_level;
	int			shake_phase;
	int			fov_phase;
	int			color_phase;
	int			intposx;
	int			intposy;
	long int	drug_time;
	double		posx;
	double		posy;
	double		posz;
	double		dirx;
	double		diry;
	double		planx;
	double		plany;
	int			walk_phase;
	int			is_falling;
	int			is_jumping;
	int			speed;
	double		jump_speed;
	int			base_dir;
}			t_player;

typedef struct data_s
{
	void		*mlx;
	void		*win;
	int			win_height;
	int			win_width;
	size_t		last_frame;
	t_player	player;
	t_map_info	map_info;
	t_key_info	key_info;
	t_mouse		mouse;
	t_img		img;
	t_texture	texture;
	t_sprite	sprite;
}				t_data;

typedef struct raystate_s
{
	double	raydirx;
	double	raydiry;
	int		x;
	int		hit;
	int		side;
	int		mapx;
	int		mapy;
	int		stepx;
	int		stepy;
	int		texx;
	int		line_height;
	int		calculated_len;
	int		offset;
	double	wallx;
	double	sidedistx;
	double	sidedisty;
	double	deltadistx;
	double	deltadisty;
	double	perpwalldist;
}				t_raystate;

typedef struct roofstate_s
{
	int		x;
	int		y;
	float	raydirx0;
	float	raydiry0;
	float	raydirx1;
	float	raydiry1;
	int		p;
	float	floorstepx;
	float	floorstepy;
	float	floorx;
	float	floory;
}			t_roofstate;

typedef struct s_sort
{
	double	dist;
	int		order;
}			t_sort;

#endif
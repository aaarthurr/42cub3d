/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arpages <arpages@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:29:44 by leoherna          #+#    #+#             */
/*   Updated: 2024/05/15 19:30:16 by arpages          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cubed.h"

#define GRID_SIZE 20
#define KEY_ESC 65307
#define KEY_A 97
#define KEY_D 100
#define KEY_S 115
#define KEY_W 119
#define KEY_LEFT 65361
#define KEY_RIGHT 65363
#define CELL_SIZE 50

int     close_window(t_data *data)
{
        //free_player(data);
        free_mapinfo(data);
        mlx_destroy_window(data->mlx, data->win);
        mlx_destroy_display(data->mlx);
        free(data->mlx);
        exit(0);
}

int	key_pressed(int keycode, t_data *data)
{
	if (keycode == KEY_ESC)
        data->key_info.key_esc = 1;
    if (keycode == KEY_S)
        data->key_info.key_s = 1;
    if (keycode == KEY_W)
        data->key_info.key_w = 1;
    if (keycode == KEY_A)
		data->key_info.key_a = 1;
    if (keycode == KEY_D)
	{
        data->key_info.key_d = 1;
	}
	if (keycode == KEY_RIGHT)
	{
		data->key_info.key_right = 1;
	}
	if (keycode == KEY_LEFT)
	{
		data->key_info.key_left = 1;
	}
	multi_key(data);
	return (0);
}

int	key_released(int keycode, t_data *data)
{
	if (keycode == KEY_ESC)
        data->key_info.key_esc = 0;
    if (keycode == KEY_S)
        data->key_info.key_s = 0;
    if (keycode == KEY_W)
        data->key_info.key_w = 0;
    if (keycode == KEY_A)
    	data->key_info.key_a = 0;
    if (keycode == KEY_D)
	{
        data->key_info.key_d = 0;
	}
	if (keycode == KEY_RIGHT)
	{
		data->key_info.key_right = 0;
	}
	if (keycode == KEY_LEFT)
	{
		data->key_info.key_left = 0;
	}
	return (0);
}

int	multi_key(t_data *data)
{
	if (data->key_info.key_esc == 1)
		close_window(data);
	if (data->key_info.key_s == 1)
		move_player(data, -1, 0);
	if (data->key_info.key_w == 1)
		move_player(data, 1, 0);
	if (data->key_info.key_a == 1)
		move_player(data, 0, -1);
	if (data->key_info.key_d == 1)
		move_player(data, 0, 1);
	if (data->key_info.key_left == 1)
		rotate_player(data, 0.2);
	if (data->key_info.key_right == 1)
		rotate_player(data, -0.2);
	//draw_grid(data, data->map_info.map);
	//draw_circle(data);
    send_rays(data);
	
	printf("%f , %f [%f, %f]\n", data->player.posX, data->player.posY, data->player.dirX, data->player.dirY);
    return (0);
}

void move_player(t_data *data, int x, int y)
{
	double prev_x;
	double prev_y;

	prev_x = data->player.posX;
	prev_y = data->player.posY;
	data->player.posX += (data->player.dirX * x) / 10;
	data->player.posY += (data->player.dirY * x) / 10;
	data->player.posX += (data->player.dirY * -y) / 10;
	data->player.posY += (data->player.dirX * y) / 10;
	if (data->map_info.map[(int)(data->player.posY)][(int)prev_x] == '1')
		data->player.posY = prev_y;
	if (data->map_info.map[(int)prev_y][(int)(data->player.posX)] == '1')
		data->player.posX = prev_x;
}
void rotate_player(t_data *data, double angle)
{
	double c_x;
	double c_y;

	c_x = data->player.dirX;
	c_y = data->player.dirY;
	data->player.dirX = (c_x * cos(angle)) - (c_y * sin(angle));
	data->player.dirY = (c_x * sin(angle)) + (c_y * cos(angle));
	c_x = data->player.planX;
	c_y = data->player.planY;
	data->player.planX = (c_x * cos(angle)) - (c_y * sin(angle));
	data->player.planY = (c_x * sin(angle)) + (c_y * cos(angle));
}

void ft_test(t_data *data)
{
	mlx_hook(data->win, 2, 1L << 0, key_pressed, data);	
	mlx_hook(data->win, 3, 1L << 1, key_released, data);
	mlx_loop(data->mlx);
}


int     game_manager(t_data *data)
{
	data->win_height = 960;
	data->win_width = 1280;
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, data->win_height, data->win_height, "Backroom cub3d"); 
	generate_base_img(data);

	printf("%d\n",tab_size(data->map_info.map));

	send_rays(data);
	//mlx_mouse_hook(data->win, mouse_move, &data);
	
	ft_test(data);
    return (0);
}

void	generate_base_img(t_data *data)
{
	data->img.img_ptr = mlx_new_image(data->mlx, data->win_width, data->win_height);
	data->img.img_char = mlx_get_data_addr(data->img.img_ptr, &(data->img.bits_pix), &(data->img.len), &(data->img.endian));
}

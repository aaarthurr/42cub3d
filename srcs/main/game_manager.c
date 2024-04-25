/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arpages <arpages@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:29:44 by leoherna          #+#    #+#             */
/*   Updated: 2024/04/25 15:20:27 by arpages          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cubed.h"


#define KEY_ESC 65307
#define KEY_A 97
#define KEY_D 100
#define KEY_S 115
#define KEY_W 119
#define KEY_LEFT 95361
#define KEY_RIGHT 65363

void move_player(t_data *data, double x, double y);
void rotate_player(t_data *data, int angle);

int     close_window(t_data *data)
{
        //free_player(data);
        free_mapinfo(data);
        mlx_destroy_window(data->mlx, data->win);
        mlx_destroy_display(data->mlx);
        free(data->mlx);
        exit(0);
}

int     event(int keycode, t_data *data)
{
	printf("%d\n", keycode);
    if (keycode == KEY_ESC)
        close_window(data);
    if (keycode == KEY_S)
    {
        move_player(data, 0, 0.1);
    }
    if (keycode == KEY_W)
    {
        move_player(data, 0, -0.1);
    }
    if (keycode == KEY_A)
    {
       move_player(data, -0.1, 0);
    }
    if (keycode == KEY_D)
    {
        move_player(data, 0.1, 0);
    }
	if (keycode == KEY_RIGHT)
		rotate_player(data, 1);
	if (keycode == KEY_LEFT)
		rotate_player(data, -1);
	
	printf("%f , %f [%f, %f]\n", data->player.posX, data->player.posY, data->player.dirX, data->player.dirY);
    return (0);
}

void move_player(t_data *data, double x, double y)
{
    data->player.posX += x;
    data->player.posY += y;
}

void rotate_player(t_data *data, int angle)
{
	double c_x;
	double c_y;

	c_x = data->player.dirX;
	c_y = data->player.dirY;
	data->player.dirX = (c_x * cos(angle)) - (c_y * sin(angle));
	data->player.dirY = (c_x * sin(angle)) + (c_y * cos(angle));
}

// void init_game(t_data *data)
// {
     
// }

int     game_manager(t_data *data)
{
    data->win_height = 480;
	data->win_width = 640;
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, data->win_height, data->win_height, "Backroom cub3d"); 


    //raycasting(data);
    mlx_key_hook(data->win, event, data);
	mlx_loop(data->mlx);
    return (0);
}

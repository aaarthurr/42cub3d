/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leoherna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:29:44 by leoherna          #+#    #+#             */
/*   Updated: 2024/04/24 16:10:03 by leoherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cubed.h"


#define KEY_ESC 65307
#define KEY_LEFT 65361
#define KEY_RIGHT 65363
#define KEY_DOWN 65364
#define KEY_UP 65362

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
        if (keycode == KEY_ESC)
                close_window(data);
        if (keycode == KEY_UP)
        {
                printf("you pressed up \n");
        }
        if (keycode == KEY_DOWN)
        {
                printf("you pressed down\n");
        }
        if (keycode == KEY_LEFT)
        {
               printf("you pressed left\n");
        }
        if (keycode == KEY_RIGHT)
        {
                printf("you pressed right\n");
        }
        return (0);
}

// void init_game(t_data *data)
// {
     
// }
 /*
int     game_manager(t_data *data)
{
        data->win_height = 480;
	data->win_width = 640;
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, data->win_height, data->win_height, "Backroom cub3d"); 


        raycasting(data);
        mlx_key_hook(data->win, event, data);
	mlx_loop(data->mlx);
        return (0);
}
*/
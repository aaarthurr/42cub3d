/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leoherna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:04:05 by arpages           #+#    #+#             */
/*   Updated: 2024/04/23 14:13:29 by leoherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	game_manager(t_data *data)
{
	data->win_height = 50;
	data->win_width = 50;
	printf("coucou\n");
	data->mlx = mlx_init();
	
	data->win = mlx_new_window(data->mlx, data->win_height, data->win_height, "Backroom cub3d");
	printf("coucou\n");
	mlx_loop(data->mlx);
}

int main(int argc, char **argv)
{
    t_data data;

    if (argc != 2)
        printf("only argument is the map path\n");
    else
    {
        data.map_info.map_path = argv[1];
        copy_file(&data.map_info);
        //print_tab(data.map_info.global);
        get_map(&data.map_info);
        print_tab(data.map_info.map);
		game_manager(&data);
    }
	return (0);
}

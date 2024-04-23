/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leoherna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:04:05 by arpages           #+#    #+#             */
/*   Updated: 2024/04/23 15:45:49 by leoherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	raycasting_try(t_data *data)
{
	data->player.posX = 22;
	data->player.posY = 12 ;   // Position de départ x et y
	
   data->player.dirX = -1;
   data->player.dirY = 0; // vecteur de direction initial
   
   data->player.planX = 0;
   data->player.planY = 0,66 ; //la version Raycaster 2D du plan de la caméra
 
  double temps = 0 ; //heure de la trame actuelle
   double oldTime = 0; //heure de l'image précédente
   
   
     for(int x = 0; x < w; x++)
    {
      //calculer la position et la direction du rayon
       double camX = 2 * x / double(w) - 1; //coordonnée x dans l'espace de la caméra
       double rayDirX = dirX + planX * camX;
      double rayDirY = dirY + planY * camX ;

}


void	game_manager(t_data *data)
{
	//locate_cube();
	//ray_cast();
    data->win_height = 480;
	data->win_width = 640;
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, data->win_height, data->win_height, "Backroom cub3d");
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
        if (check_walls(&data) == 0)
            printf("error\n");
		//game_manager(&data);
    }
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leoherna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:57:52 by leoherna          #+#    #+#             */
/*   Updated: 2024/04/24 14:57:52 by leoherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	free_img(t_data *data)
{
	if(data->texture.ceiling_color_or_texture == 1)
		mlx_destroy_image(data->mlx, data->texture.ceiling.img_ptr);
	mlx_destroy_image(data->mlx, data->texture.Nwall.img_ptr);
    mlx_destroy_image(data->mlx, data->texture.Swall.img_ptr);
	mlx_destroy_image(data->mlx, data->texture.Wwall.img_ptr);
	mlx_destroy_image(data->mlx, data->texture.Ewall.img_ptr);
	mlx_destroy_image(data->mlx, data->img.img_ptr);
}

void	free_line(t_data *data)
{

	// printf("1---------------\n");
	// print_tab(data->map_info.global);
	// 	printf("2---------------\n");
	// print_tab(data->map_info.map);
	// 	printf("3---------------\n");
	// //print_tab(data->map_info.info);

	free_tab(data->map_info.global);
	free_tab(data->map_info.map);
	//free_tab(data->map_info.info);

	free(data->texture.Nwall_path);
	free(data->texture.Swall_path);
	free(data->texture.Wwall_path);
	free(data->texture.Ewall_path);
	if (data->texture.ceiling_color_or_texture == 1)
		free(data->texture.ceiling_path);
}

void    free_mapinfo(t_data *data)
{
	free_img(data);
	free_line(data);
	printf("salut %f\n", data->player.dirY);

}
void free_tab(char **tab)
{
    int i;

    if (!tab)
        return;

    i = 0;
    while (tab[i] != NULL)
    {
        free(tab[i]);
        tab[i] = NULL; // Bonne pratique pour éviter des double free
        i++;
    }
    free(tab);
    tab = NULL; // Idem, bonne pratique pour sécuriser
}

void exit_manager(t_data *data)
{
	exit(0);
}
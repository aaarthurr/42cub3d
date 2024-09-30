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
	if (data->texture.ceiling_color_or_texture == 1)
		mlx_destroy_image(data->mlx, data->texture.ceiling.img_ptr);
	mlx_destroy_image(data->mlx, data->texture.Nwall.img_ptr);
	mlx_destroy_image(data->mlx, data->texture.Swall.img_ptr);
	mlx_destroy_image(data->mlx, data->texture.Wwall.img_ptr);
	mlx_destroy_image(data->mlx, data->texture.Ewall.img_ptr);
	mlx_destroy_image(data->mlx, data->texture.pills.img_ptr);
	free(data->sprite.Zbuffer);
	free(data->sprite.pills);
	mlx_destroy_image(data->mlx, data->img.img_ptr);
}

void	free_line(t_data *data)
{
	free_tab(data->map_info.global);
	free_tab(data->map_info.map);
}

void	free_texture(t_data *data)
{
	if (data->texture.Nwall_path)
		free(data->texture.Nwall_path);
	if (data->texture.Swall_path)
		free(data->texture.Swall_path);
	if (data->texture.Wwall_path)
		free(data->texture.Wwall_path);
	if (data->texture.Ewall_path)
		free(data->texture.Ewall_path);
	if (data->texture.ceiling_color_or_texture == 1)
		free(data->texture.ceiling_path);
}

void	free_function(t_data *data)
{
	free_img(data);
	free_texture(data);
	free_line(data);
}

void	exit_manager(t_data *data)
{
	mlx_destroy_image(data->mlx, data->img.img_ptr);
	free_texture(data);
	free_line(data);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit(0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 15:21:58 by arthur            #+#    #+#             */
/*   Updated: 2024/05/29 12:35:47 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	get_image(t_data *data)
{
	int	x;
	int	y;

	x = 512;
	y = 512;

	data->texture.wall.img_ptr = NULL;
	
	if (access("textures/wall_bis.xpm", F_OK) == -1)
    {
        fprintf(stderr, "Error: file %s not found\n", "textures/wall.xpm");
        return ;
    }
	data->texture.wall.img_ptr = mlx_xpm_file_to_image(data->mlx, "textures/wall_bis.xpm", &x, &y);
}

void	create_image(t_data *data)
{
	data->texture.wall.img_char = mlx_get_data_addr(data->texture.wall.img_ptr, &data->texture.wall.bits_pix, &data->texture.wall.len, &data->texture.wall.endian);
	data->texture.wall.global_color = blend_color(&data->texture.wall);
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leoherna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 15:21:58 by arthur            #+#    #+#             */
/*   Updated: 2024/09/24 13:55:46 by leoherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	get_image(t_data *data)
{
	int	x;
	int	y;

	x = TEX_SIZE;
	y = TEX_SIZE;

	data->texture.wall.img_ptr = NULL;
    data->texture.ceiling.img_ptr = NULL;

    data->texture.wall.img_ptr = mlx_xpm_file_to_image(data->mlx, "textures/textwall_v2.xpm", &x, &y);
    data->texture.ceiling.img_ptr = mlx_xpm_file_to_image(data->mlx, "textures/ceiling.xpm", &x, &y);
}

void    create_image(t_data *data)
{
    data->texture.wall.img_char = mlx_get_data_addr(data->texture.wall.img_ptr, &data->texture.wall.bits_pix, &data->texture.wall.len, &data->texture.wall.endian);
    data->texture.wall.global_color = blend_color(&data->texture.wall);

    data->texture.ceiling.img_char = mlx_get_data_addr(data->texture.ceiling.img_ptr, &data->texture.ceiling.bits_pix, &data->texture.ceiling.len, &data->texture.ceiling.endian);
    data->texture.ceiling.global_color = blend_color(&data->texture.ceiling);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opti.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leoherna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:53:52 by arpages           #+#    #+#             */
/*   Updated: 2024/09/30 10:48:39 by leoherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	pixel_put_opti(t_img *img, int x, int y, int color)
{
	int	offset;

	offset = (img->len * y) + (x * (img->bits_pix / 8));
	*((unsigned int *)(offset + img->img_char)) = color;
}

void	drawverticalline(t_data *data, t_raystate *raystate, int lstart, int lend, t_img *img)
{
	int		y;
	int		color;
	double	step;
	double	tex_pos;
	int		tex_y;

	step = 1.0 * TEX_SIZE / raystate->line_height;
	tex_pos = ((lstart - raystate->offset) - data->win_height / 2 + raystate->line_height / 2) * step;
	y = 0;
	data->sprite.Zbuffer[raystate->x] = raystate->perpWallDist;
	while (y < lstart)
	{
		if (data->player.drug_level < 5)
		{
			if (data->texture.ceiling_color_or_texture == 0)
			{
				pixel_put_opti(&(data->img), raystate->x, y, data->texture.ceiling_color);
			}
		}
		y++;
	}
	while (y < lend)
	{
		tex_y = (int)tex_pos & (TEX_SIZE - 1);
		tex_pos += step;
		color = get_pixel_color(img, raystate->texX, tex_y);
		color = assombrircouleur(color, raystate->perpWallDist * (raystate->perpWallDist / 2));
		if (data->player.drug_level >= 9)
			color = give_lsd(data, color);
		pixel_put_opti(&(data->img), raystate->x, y, color);
		y++;
	}
	while (y < data->win_height)
	{
		if (data->player.drug_level < 5)
		{
			pixel_put_opti(&(data->img), raystate->x, y, data->texture.floor_color);
		}
		y++;
	}
}

int	get_pixel_color(t_img *img, int x, int y)
{
	int	color;
	int	pixel_index;

	if (x < 0 || x >= TEX_SIZE || y < 0 || y >= TEX_SIZE)
	{
		fprintf(stderr,
			"Les coordonnées sont en dehors des limites de l'image.\n");
		return (-1);
	}
	pixel_index = (y * img->len) + (x * (img->bits_pix / 8));
	color = *(int *)(img->img_char + pixel_index);
	return (color);
}

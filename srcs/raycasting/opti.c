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

void	drawverticalline_bis(t_data *data, t_raystate *raystate,
		t_var *var, t_img *img)
{
	while (var->y < var->lend)
	{
		var->x = (int)var->d_b & (TEX_SIZE - 1);
		var->d_b += var->d_a;
		var->c = get_pixel_color(img, raystate->texx, var->x);
		var->c = assombrircouleur(var->c, raystate->perpwalldist
				* (raystate->perpwalldist / 2));
		if (data->player.drug_level >= 9)
			var->c = give_lsd(data, var->c);
		pixel_put_opti(&(data->img),
			raystate->x, var->y, var->c);
		var->y++;
	}
	while (var->y < data->win_height)
	{
		if (data->player.drug_level < 5)
			pixel_put_opti(&(data->img),
				raystate->x, var->y, data->texture.floor_color);
		var->y++;
	}
}

void	drawverticalline(t_data *data, t_raystate *raystate,
	t_img *img, t_var *var)
{
	var->d_a = 1.0 * TEX_SIZE / raystate->line_height;
	var->d_b = ((var->lstart - raystate->offset) - data->win_height
			/ 2 + raystate->line_height / 2) * var->d_a;
	var->y = 0;
	data->sprite.zbuffer[raystate->x] = raystate->perpwalldist;
	while (var->y < var->lstart)
	{
		if (data->player.drug_level < 5)
		{
			if (data->texture.ceiling_color_or_texture == 0)
				pixel_put_opti(&(data->img),
					raystate->x, var->y, data->texture.ceiling_color);
		}
		var->y++;
	}
	drawverticalline_bis(data, raystate, var, img);
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

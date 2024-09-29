/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opti.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:53:52 by arpages           #+#    #+#             */
/*   Updated: 2024/09/29 15:34:03 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"


#include "cubed.h"

void    pixel_put_opti(t_img *img, int x, int y, int color)
{
    int offset;
	
	offset = (img->len * y) + (x * (img->bits_pix / 8));
	*((unsigned int *)(offset + img->img_char)) = color;
}

void drawVerticalLine(t_data *data, t_raystate *raystate, int lStart, int lEnd, t_img *img) 
{
    int y;
	int color;
	double	step;
	double	texPos;
	
	// Starting texture coordinate
	step = 1.0 * TEX_SIZE / raystate->line_height;
	texPos = ((lStart - raystate->offset) - data->win_height / 2 + raystate->line_height / 2) * step;
	y = 0;
	data->sprite.Zbuffer[raystate->x] = raystate->perpWallDist;
	while (y < lStart)
	{
		if (data->player.drug_level < 7)
		{
			if (data->texture.ceiling_color_or_texture == 0)
			{
				pixel_put_opti(&(data->img), raystate->x, y, data->texture.ceiling_color);
			}
		}
		y++;
	}
	while(y < lEnd)
	{
		int texY = (int)texPos & (TEX_SIZE - 1);
		texPos += step;
		color = get_pixel_color(img, raystate->texX, texY);
		color = assombrirCouleur(color, raystate->perpWallDist * (raystate->perpWallDist / 2));
		if (data->player.drug_level >= 5)
			color = give_lsd(data, color);
		pixel_put_opti(&(data->img), raystate->x, y, color);
		y++;
	}
	while (y < data->win_height)
	{
		if (data->player.drug_level < 7)
		{
			pixel_put_opti(&(data->img), raystate->x, y, data->texture.floor_color); //chamger sol
		}
		y++;
	}
}

int get_pixel_color(t_img *img, int x, int y)
{
    int color;
    if (x < 0 || x >= TEX_SIZE || y < 0 || y >= TEX_SIZE)
    {
        fprintf(stderr, "Les coordonnées sont en dehors des limites de l'image.\n");
        return -1;
    }
    int pixel_index = (y * img->len) + (x * (img->bits_pix / 8));
    color = *(int *)(img->img_char + pixel_index);
    return color;
}

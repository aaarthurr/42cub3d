/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opti.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leoherna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:53:52 by arpages           #+#    #+#             */
/*   Updated: 2024/09/28 14:57:21 by leoherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		if (data->player.drug_level <= 1)
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
		// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
		int texY = (int)texPos & (TEX_SIZE - 1);
		texPos += step;
		
		//color = 0x1FF4DE;
		
		color = get_pixel_color(img, raystate->texX, texY);
		//color = get_smoothed_color(img, color, (raystate->perpWallDist / (data->win_width / 200)));
		color = assombrirCouleur(color, raystate->perpWallDist * (raystate->perpWallDist / 2));
		if (data->player.drug_level >= 1)
			color = give_lsd(color);
		pixel_put_opti(&(data->img), raystate->x, y, color);
		y++;
	}
	while (y < data->win_height)
	{
		pixel_put_opti(&(data->img), raystate->x, y, data->texture.floor_color); //chamger sol
		y++;
	}
}

int	get_smoothed_color(t_img *img, int base_color, double power)
{
	int	colors[3];
	
	power -= 3;
	if (power <= 0)
		return (base_color);
	colors[0] = (base_color >> 16) & 0xFF;
    colors[1] = (base_color >> 8) & 0xFF;
    colors[2] = base_color & 0xFF;
	colors[0] += ((img->global_color >> 16) & 0xFF) * power;
    colors[1] += ((img->global_color >> 8) & 0xFF) * power;
    colors[2] += (img->global_color & 0xFF) * power;
	colors[0] = colors[0] / (power + 1);
	colors[1] = colors[1] / (power + 1);
    colors[2] = colors[2] / (power + 1);
	int nouvelleCouleur = (colors[0] << 16) | (colors[1] << 8) | colors[2];
	return (nouvelleCouleur);
}


int	blend_color(t_img *img)
{
	int temp_color;
	int	colors[3];
	int offset_x;
	int offset_y;
	int i;
	
	offset_x = 0;
	colors[0] = 0;
    colors[1] = 0;
    colors[2] = 0;
	i = 0;
	while (offset_x < TEX_SIZE)
	{
		offset_y = 0;
		while (offset_y < TEX_SIZE)
		{
			temp_color = get_pixel_color(img, offset_x, offset_y);
			colors[0] += (temp_color >> 16) & 0xFF;
    		colors[1] += (temp_color >> 8) & 0xFF;
    		colors[2] += temp_color & 0xFF;
			i++;
			offset_y += 50;
		}
		offset_x += 50;
	}
	colors[0] = colors[0] / i;
	colors[1] = colors[1] / i;
    colors[2] = colors[2] / i;
	int nouvelleCouleur = (colors[0] << 16) | (colors[1] << 8) | colors[2];
	return (nouvelleCouleur);
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

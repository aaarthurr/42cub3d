/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opti.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arpages <arpages@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:53:52 by arpages           #+#    #+#             */
/*   Updated: 2024/05/15 19:35:30 by arpages          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void    pixel_put_opti(t_img *img, int x, int y, int color)
{
    int offset;
	
	offset = (img->len * y) + (x * (img->bits_pix / 8));
	*((unsigned int *)(offset + img->img_char)) = color;
}

void drawVerticalLine(t_img *img, int x, int yMin, int yMax, int color, int height) 
{
    int y;

	y = 0;
	while (y < height)
	{
		if (y >= yMin && y <= yMax)
			pixel_put_opti(img, x, y, color);
		else
			pixel_put_opti(img, x, y, 0x000000);
		y++;
	}
	
    for (y = yMin; y <= yMax; y++) {
        
    }
}

void clearScreen(t_img *img, int width, int height) 
{
    int x, y;
    for (x = 0; x < width; x++) {
        for (y = 0; y < height; y++) {
            pixel_put_opti(img, x, y, 0x000000); // Noir en hexadécimal
        }
    }
}
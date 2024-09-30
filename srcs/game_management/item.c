/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   item.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leoherna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 10:56:18 by leoherna          #+#    #+#             */
/*   Updated: 2024/09/25 10:56:18 by leoherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	sort_sprite(int *order, double *dist, int amount)
{
	int		i;
	t_sort	*sprites;

	i = 0;
	sprites = (t_sort *)malloc(amount * sizeof(t_sort));
	if (sprites == NULL)
	{
		printf("Erreur d'allocation mémoire.\n");
		return ;
	}
	while (i < amount)
	{
		sprites[i].dist = dist[i];
		sprites[i].order = order[i];
		i++;
	}
	qsort(sprites, amount, sizeof(t_sort), comparesprites);
	i = 0;
	while (i < amount)
	{
		dist[i] = sprites[i].dist;
		order[i] = sprites[i].order;
		i++;
	}
	free(sprites);
}

void	draw_sprite_line(t_data *data, t_spritestate *sp)
{
	t_var	var;

	var.a = sp->drawStartX;
	while (var.a < sp->drawEndX)
	{
		var.x = (int)((256 * (var.a - (-sp->spriteWidth / 2
							+ sp->spriteScreenX))
					* SPRITE_SIZE / sp->spriteWidth) / 256);
		var.d_a = sp->drawStartY;
		if (sp->transformY > 0 && var.a > 0 && var.a < data->win_width
			&& sp->transformY < data->sprite.Zbuffer[var.a])
		{
			while (var.d_a < sp->drawEndY)
			{
				var.b = (var.d_a) * 256 - data->win_height
					* 128 + sp->spriteHeight * 128;
				var.y = ((var.b * SPRITE_SIZE) / sp->spriteHeight) / 256;
				var.c = get_pixel_color(&(data->texture.pills), var.x, var.y);
				if (var.c > 0)
					pixel_put_opti(&(data->img), var.a, var.d_a, var.c);
				var.d_a++;
			}
		}
		var.a++;
	}
}

void	draw_sprite_bis(t_data *data, int *Order, int i, t_spritestate *sp)
{
	sp->spriteX = data->sprite.pills[Order[i]].x - data->player.posX;
	sp->spriteY = data->sprite.pills[Order[i]].y - data->player.posY;
	sp->invDet = 1.0 / (data->player.planX * data->player.dirY
			- data->player.dirX * data->player.planY);
	sp->transformX = sp->invDet * (data->player.dirY * sp->spriteX
			- data->player.dirX * sp->spriteY);
	sp->transformY = sp->invDet * (-data->player.planY * sp->spriteX
			+ data->player.planX * sp->spriteY);
	sp->spriteScreenX = (int)((data->win_width / 2)
			* (1 + sp->transformX / sp->transformY));
	sp->spriteHeight = abs((int)(data->win_height / sp->transformY));
	sp->drawStartY = -(sp->spriteHeight) / 2 + data->win_height / 2;
	sp->drawEndY = sp->spriteHeight / 2 + data->win_height / 2;
	sp->calculated_len = sp->drawEndY - sp->drawStartY;
}

void	draw_sprite(t_data *data, int *spriteOrder, int i)
{
	t_spritestate	sp;

	draw_sprite_bis(data, spriteOrder, i, &sp);
	if (sp.drawStartY < 0)
		sp.drawStartY = 0;
	if (sp.drawEndY >= data->win_height)
		sp.drawEndY = data->win_height - 1;
	sp.spriteWidth = abs((int)(data->win_height / sp.transformY));
	sp.drawStartX = -(sp.spriteWidth) / 2 + sp.spriteScreenX;
	sp.drawEndX = sp.spriteWidth / 2 + sp.spriteScreenX;
	if (sp.drawStartX < 0)
		sp.drawStartX = 0;
	if (sp.drawEndX >= data->win_width)
		sp.drawEndX = data->win_width - 1;
	draw_sprite_line(data, &sp);
}

void	cast_sprite(t_data *data)
{
	int		i;
	int		*spriteorder;
	double	*spritedistance;

	spriteorder = malloc(sizeof(int) * data->sprite.number);
	spritedistance = malloc(sizeof(double) * data->sprite.number);
	i = 0;
	while (i < data->sprite.number)
	{
		cast_sprite_bis(data, i, &spriteorder, &spritedistance);
		i++;
	}
	sort_sprite(spriteorder, spritedistance, data->sprite.number);
	i = 0;
	while (i < data->sprite.number)
	{
		cast_sprite_ter(data, i, &spriteorder);
		i++;
	}
	free(spritedistance);
	free(spriteorder);
}

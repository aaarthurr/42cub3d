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

int	comparesprites(const void *a, const void *b)
{
	t_sort	*sprite_a;
	t_sort	*sprite_b;

	sprite_a = (t_sort *)a;
	sprite_b = (t_sort *)b;
	if (sprite_a->dist < sprite_b->dist)
		return (1);
	if (sprite_a->dist > sprite_b->dist)
		return (-1);
	return (0);
}

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
	int		stripe;
	double	y;
	int		d;

	stripe = sp->drawStartX;
	while (stripe < sp->drawEndX)
	{
		var.x = (int)((256 * (stripe - (-sp->spriteWidth / 2
							+ sp->spriteScreenX))
					* SPRITE_SIZE / sp->spriteWidth) / 256);
		y = sp->drawStartY;
		if (sp->transformY > 0 && stripe > 0 && stripe < data->win_width
			&& sp->transformY < data->sprite.Zbuffer[stripe])
		{
			while (y < sp->drawEndY)
			{
				d = (y) * 256 - data->win_height * 128 + sp->spriteHeight * 128;
				var.y = ((d * SPRITE_SIZE) / sp->spriteHeight) / 256;
				var.c = get_pixel_color(&(data->texture.pills), var.x, var.y);
				if (var.c > 0)
					pixel_put_opti(&(data->img), stripe, y, var.c);
				y++;
			}
		}
		stripe++;
	}
}

void	draw_sprite(t_data *data, int *spriteOrder, int i)
{
	t_spritestate	sp;

	sp.spriteX = data->sprite.pills[spriteOrder[i]].x - data->player.posX;
	sp.spriteY = data->sprite.pills[spriteOrder[i]].y - data->player.posY;
	sp.invDet = 1.0 / (data->player.planX * data->player.dirY - data->player.dirX * data->player.planY);
	sp.transformX = sp.invDet * (data->player.dirY * sp.spriteX - data->player.dirX * sp.spriteY);
	sp.transformY = sp.invDet * (-data->player.planY * sp.spriteX + data->player.planX * sp.spriteY);
	sp.spriteScreenX = (int)((data->win_width / 2) * (1 + sp.transformX / sp.transformY));
	sp.spriteHeight = abs((int)(data->win_height / sp.transformY));
	sp.drawStartY = -(sp.spriteHeight) / 2 + data->win_height / 2;
	sp.drawEndY = sp.spriteHeight / 2 + data->win_height / 2;
	sp.calculated_len = sp.drawEndY - sp.drawStartY;
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
		spriteorder[i] = i;
		data->sprite.pills[i].index = i;
		spritedistance[i] = ((data->player.posX - data->sprite.pills[i].x)
				* (data->player.posX - data->sprite.pills[i].x)
				+ (data->player.posY - data->sprite.pills[i].y)
				* (data->player.posY - data->sprite.pills[i].y));
		data->sprite.pills[i].distance = spritedistance[i];
		i++;
	}
	sort_sprite(spriteorder, spritedistance, data->sprite.number);
	i = 0;
	while (i < data->sprite.number)
	{
		if (data->sprite.pills[spriteorder[i]].distance < 0.5 && data->sprite.pills[spriteorder[i]].taken == 0)
		{
			take_drugs(data);
			data->sprite.pills[spriteorder[i]].taken = 1;
		}
		if (data->sprite.pills[spriteorder[i]].taken == 0)
			draw_sprite(data, spriteorder, i);
		i++;
	}
	free(spritedistance);
	free(spriteorder);
}

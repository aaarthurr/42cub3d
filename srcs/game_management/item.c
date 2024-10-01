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

	var.a = sp->drawstartx;
	while (var.a < sp->drawendx)
	{
		var.x = (int)((256 * (var.a - (-sp->spritewidth / 2
							+ sp->spritescreenx))
					* SPRITE_SIZE / sp->spritewidth) / 256);
		var.d_a = sp->drawstarty;
		if (sp->transformy > 0 && var.a > 0 && var.a < data->win_width
			&& sp->transformy < data->sprite.zbuffer[var.a])
		{
			while (var.d_a < sp->drawendy)
			{
				var.b = (var.d_a) * 256 - data->win_height
					* 128 + sp->spriteheight * 128;
				var.y = ((var.b * SPRITE_SIZE) / sp->spriteheight) / 256;
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
	sp->spritex = data->sprite.pills[Order[i]].x - data->player.posx;
	sp->spritey = data->sprite.pills[Order[i]].y - data->player.posy;
	sp->invdet = 1.0 / (data->player.planx * data->player.diry
			- data->player.dirx * data->player.plany);
	sp->transformx = sp->invdet * (data->player.diry * sp->spritex
			- data->player.dirx * sp->spritey);
	sp->transformy = sp->invdet * (-data->player.plany * sp->spritex
			+ data->player.planx * sp->spritey);
	sp->spritescreenx = (int)((data->win_width / 2)
			* (1 + sp->transformx / sp->transformy));
	sp->spriteheight = abs((int)(data->win_height / sp->transformy));
	sp->drawstarty = -(sp->spriteheight) / 2 + data->win_height / 2;
	sp->drawendy = sp->spriteheight / 2 + data->win_height / 2;
	sp->calculated_len = sp->drawendy - sp->drawstarty;
}

void	draw_sprite(t_data *data, int *spriteOrder, int i)
{
	t_spritestate	sp;

	draw_sprite_bis(data, spriteOrder, i, &sp);
	if (sp.drawstarty < 0)
		sp.drawstarty = 0;
	if (sp.drawendy >= data->win_height)
		sp.drawendy = data->win_height - 1;
	sp.spritewidth = abs((int)(data->win_height / sp.transformy));
	sp.drawstartx = -(sp.spritewidth) / 2 + sp.spritescreenx;
	sp.drawendx = sp.spritewidth / 2 + sp.spritescreenx;
	if (sp.drawstartx < 0)
		sp.drawstartx = 0;
	if (sp.drawendx >= data->win_width)
		sp.drawendx = data->win_width - 1;
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

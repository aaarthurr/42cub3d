/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   item_ter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leoherna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 10:56:18 by leoherna          #+#    #+#             */
/*   Updated: 2024/09/25 10:56:18 by leoherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	cast_sprite_bis(t_data *data, int i, int **spriteorder,
	double **spritedistance)
{
	(*spriteorder)[i] = i;
	data->sprite.pills[i].index = i;
	(*spritedistance)[i] = ((data->player.posx - data->sprite.pills[i].x)
			* (data->player.posx - data->sprite.pills[i].x)
			+ (data->player.posy - data->sprite.pills[i].y)
			* (data->player.posy - data->sprite.pills[i].y));
	data->sprite.pills[i].distance = (*spritedistance)[i];
}

void	cast_sprite_ter(t_data *data, int i, int **spriteorder)
{
	if (data->sprite.pills[(*spriteorder)[i]].distance < 0.5
			&& data->sprite.pills[(*spriteorder)[i]].taken == 0)
	{
		take_drugs(data);
		data->sprite.pills[(*spriteorder)[i]].taken = 1;
	}
	if (data->sprite.pills[(*spriteorder)[i]].taken == 0)
		draw_sprite(data, (*spriteorder), i);
}

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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   item_bis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arpages <arpages@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 15:38:09 by arpages           #+#    #+#             */
/*   Updated: 2024/09/30 15:55:39 by arpages          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

int	set_items_coordonnates(t_data *data, t_pills *pill)
{
	int	i;
	int	j;
	int	cap;

	cap = 0;
	i = 0;
	j = 0;
	while (data->map_info.map[i][j] != '0' && cap < 25)
	{
		i = rand() % data->map_info.height;
		j = rand() % ft_strlen(data->map_info.map[i]);
		cap++;
		if (data->map_info.map[i][j] == '0' && is_a_pill_here(data, j, i) == 0)
		{
			pill->y = i + 0.5;
			pill->x = j + 0.5;
			return (0);
		}
	}
	return (1);
}

t_pills	*set_up_items(t_data *data, int number)
{
	t_pills	*pills;
	int		i;

	i = 0;
	pills = malloc(sizeof(t_pills) * number);
	data->sprite.pills = pills;
	init_pills(data);
	while (i < number)
	{
		set_items_coordonnates(data, &(pills[i]));
		i++;
	}
	return (pills);
}

void	set_sprite(t_data *data, int number)
{
	data->sprite.number = number;
	data->sprite.zbuffer = malloc(sizeof(double) * data->win_width);
	data->sprite.pills = set_up_items(data, number);
}

int	is_a_pill_here(t_data *data, float x, float y)
{
	int	i;

	i = 0;
	while (i < data->sprite.number)
	{
		if (data->sprite.pills[i].x == x + 0.5
			&& data->sprite.pills[i].y == y + 0.5)
		{
			return (1);
		}
		i++;
	}
	return (0);
}

void	init_pills(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->sprite.number)
	{
		data->sprite.pills[i].x = 0;
		data->sprite.pills[i].y = 0;
		data->sprite.pills[i].taken = 0;
		i++;
	}
}

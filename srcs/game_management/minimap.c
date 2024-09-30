/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arpages <arpages@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 15:44:31 by arpages           #+#    #+#             */
/*   Updated: 2024/09/30 15:44:31 by arpages          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	draw_player_mini_map(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (x < 6)
	{
		y = 0;
		while (y < 6)
		{
			pixel_put_opti(&(data->img), x + 62, y + 62, 0xFF2222);
			y++;
		}
		x++;
	}
	x = 0;
}

void	draw_carre_mini_map(t_data *data, int pos_x, int pos_y)
{
	int	x;
	int	y;

	x = -2;
	y = -2;
	while (x < 2)
	{
		y = -2;
		while (y < 2)
		{
			pixel_put_opti(&(data->img), x + pos_x, y + pos_y, 0x229922);
			y++;
		}
		x++;
	}
	x = 0;
}

void	draw_item_on_map(t_data *data)
{
	double	x;
	double	y;

	x = -6;
	y = -6;
	while (x < 6)
	{
		y = -6;
		while (y < 6)
		{
			if (is_item_from_player(data, x, y) == 1)
				draw_carre_mini_map(data, (int)(x * 10)
					+ 65, (int)(y * 10 + 65));
			y += 0.1;
		}
		x += 0.1;
	}
}

void	print_map(t_data *data)
{
	double	x;
	double	y;

	x = -6;
	y = -6;
	while (x < 6)
	{
		y = -6;
		while (y < 6)
		{
			if (is_wall_from_player(data, x, y) == 1)
				pixel_put_opti(&(data->img), (int)(x * 10) + 65,
					(int)((y * 10) + 65), 0x000000);
			else
				pixel_put_opti(&(data->img), (int)(x * 10) + 65,
					(int)((y * 10) + 65), 0xFFFFFF);
			y += 0.1;
		}
		x += 0.1;
	}
	draw_item_on_map(data);
	draw_player_mini_map(data);
}

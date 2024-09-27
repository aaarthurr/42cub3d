/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leoherna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 13:58:21 by arpages           #+#    #+#             */
/*   Updated: 2024/09/28 15:21:57 by leoherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

int	check_walls(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (data->map_info.map[y] != NULL)
	{
		x = 0;
		while (ft_strchr(data->map_info.map[y][x], " 10NSEW") == 1)
		{
			if (ft_strchr(data->map_info.map[y][x], " 10NSEW") == 0)
				return (1);
			if (ft_strchr(data->map_info.map[y][x], "NSEW") == 1)
				set_pos(data, x, y, data->map_info.map[y][x]);
			if (ft_strchr(data->map_info.map[y][x], "0NSEW") == 1)
			{
				if (check_walls_bis(data, x, y) == 1)
					return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

int	check_walls_bis(t_data *data, int x, int y)
{
	if (ft_strchr(data->map_info.map[y][x - 1], "10NSEW") == 0)
		return (1);
	else if (ft_strchr(data->map_info.map[y][x + 1], "10NSEW") == 0)
		return (1);
	else if (ft_strchr(data->map_info.map[y - 1][x], "10NSEW") == 0)
		return (1);
	else if (ft_strchr(data->map_info.map[y + 1][x], "10NSEW") == 0)
		return (1);
	return (0);
}

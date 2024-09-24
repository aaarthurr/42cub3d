/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leoherna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 13:58:21 by arpages           #+#    #+#             */
/*   Updated: 2024/09/24 10:22:26 by leoherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

int	check_elements(t_data *data)
{
	int	x;
	int	y;
	int	things;

	y = -1;
	things = 0;
	while (data->map_info.map[++y])
	{
		x = -1;
		while (data->map_info.map[y][++x])
		{
			if (data->map_info.map[y][x] != '\n'
				&& data->map_info.map[y][x] != '1'
				&& data->map_info.map[y][x] != '0'
				&& data->map_info.map[y][x] != ' '
				&& data->map_info.map[y][x] != 'S'
				&& data->map_info.map[y][x] != 'W'
				&& data->map_info.map[y][x] != 'E'
				&& data->map_info.map[y][x] != 'N'
				&& data->map_info.map[y][x] != 'D')
				things++;
		}
	}
	if (things != 0)
		return (1);
	return (0);
}

int check_walls(t_data *data)
{
	int x;
	int y;

	y = 0;
	while (data->map_info.map[y] != NULL)
	{
		x = 0;
		while (ft_strchr(data->map_info.map[y][x], " 10NSEW") == 1)
		{
			if (ft_strchr(data->map_info.map[y][x], " 10NSEW") == 0)
				return (1);
			if (ft_strchr(data->map_info.map[y][x], "NSEW") == 1)
				set_pos(data, x ,y, data->map_info.map[y][x]);
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

int check_walls_bis(t_data *data, int x, int y)
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

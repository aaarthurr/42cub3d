/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arpages <arpages@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 15:44:31 by arpages           #+#    #+#             */
/*   Updated: 2024/09/30 15:44:31 by arpages          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

int	is_wall_from_player(t_data *data, double x, double y)
{
	double	m_x;
	double	m_y;

	m_x = data->player.posx + x;
	m_y = data->player.posy + y;
	if (m_x < 0 || m_y < 0)
		return (1);
	if (data->map_info.height < m_y)
		return (1);
	if (ft_strlen(data->map_info.map[(int)(m_y)]) < m_x)
		return (1);
	if (ft_strchr(data->map_info.map[(int)(m_y)][(int)(m_x)], " 1\n\0") == 1)
		return (1);
	return (0);
}

int	is_item_from_player(t_data *data, double x, double y)
{
	double	m_x;
	double	m_y;
	int		i;

	m_x = floor((data->player.posx + x) * 10) / 10;
	m_y = floor((data->player.posy + y) * 10) / 10;
	i = 0;
	while (i < data->sprite.number)
	{
		if (data->sprite.pills[i].x == m_x && data->sprite.pills[i].y == m_y
			&& data->sprite.pills[i].taken == 0 && data->sprite.pills[i].x != 0)
			return (1);
		i++;
	}
	return (0);
}

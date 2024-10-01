/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finding.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leoherna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 14:01:57 by leoherna          #+#    #+#             */
/*   Updated: 2024/09/23 14:01:57 by leoherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

int	count_line(char **tab)
{
	int	j;

	j = 0;
	if (tab == NULL)
		return (0);
	while (tab[j] != NULL)
		j++;
	return (j);
}

char	**duplicata_map(t_data *data)
{
	t_var	var;
	char	**map;

	var.x = 0;
	var.y = 0;
	data->map_info.height = count_line(data->map_info.map);
	var.nb_line = data->map_info.height;
	map = malloc(sizeof(char *) * (data->map_info.height + 1));
	while (var.y != var.nb_line)
	{
		map[var.y] = malloc(sizeof(char)
				* (ft_strlen(data->map_info.map[var.y]) + 1));
		if (!map[var.y])
			return (NULL);
		while (data->map_info.map[var.y][var.x] != '\0'
				&& data->map_info.map[var.y][var.x] != '\n')
		{
			map[var.y][var.x] = data->map_info.map[var.y][var.x];
			var.x++;
		}
		map[var.y][var.x] = '\0';
		var.x = 0;
		var.y++;
	}
	return (map[var.y] = NULL, map);
}

int	should_i_be_here(int wcase, t_actpos act, char **map, t_data *data)
{
	if (wcase == 1)
		if (act.act_y + 1 > data->map_info.height)
			return (1);
	if (wcase == 2)
		if (act.act_y - 1 <= 0)
			return (1);
	if (wcase == 3)
		if (act.act_x - 1 < 0)
			return (1);
	if (wcase == 4)
		if (act.act_x + 1 > ft_strlen(map[act.act_y]))
			return (1);
	return (0);
}

void	path_free_map(t_data *data, char **map)
{
	int	i;

	i = data->map_info.height;
	if (!map[0])
		return ;
	while (i != -1)
	{
		free(map[i]);
		i--;
	}
	free(map);
}

int	path_finding(t_data *data)
{
	t_pos		pos[1024];
	t_actpos	act;
	t_var		var;

	var.tab = duplicata_map(data);
	if (!var.tab)
		return (1);
	var.top = 1;
	act.act_x = 0;
	act.act_y = 0;
	pos[0].x = data->player.intposx;
	pos[0].y = data->player.intposy;
	while (var.top > 0)
	{
		var.top--;
		act.act_x = pos[var.top].x;
		act.act_y = pos[var.top].y;
		if (try_up_down(data, act, pos, &var) == 1)
			return (path_free_map(data, var.tab), 1);
		if (try_left_right(data, act, pos, &var) == 1)
			return (path_free_map(data, var.tab), 1);
	}
	path_free_map(data, var.tab);
	return (0);
}

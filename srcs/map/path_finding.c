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


int count_line(char **tab)
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
	char	**map;
    int nb_line;
    int x;
    int y;

    x = 0;
    y = 0;
	//map = NULL;
	//printf("taille de la map : %d\n", data->map_info.height);
	data->map_info.height = count_line(data->map_info.map);
    nb_line = data->map_info.height;
    map = malloc(sizeof(char *) * (data->map_info.height + 1));
    while (y != nb_line)
    {
        map[y] = malloc(sizeof(char) * (ft_strlen(data->map_info.map[y]) + 1));
        if (!map[y])
            return (NULL);
        while(data->map_info.map[y][x] != '\0' && data->map_info.map[y][x] != '\n')
        {
            map[y][x] = data->map_info.map[y][x];
            x++;
        }
        map[y][x] ='\0';
		//printf("%s\n",map[y]);
        x = 0;
        y++;
    }
    map[y] = NULL;
	return (map);
}

int should_i_be_here(int wcase , t_actpos act, char **map, t_data *data)
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


int	try_up_down(t_data *data, t_actpos act, int *top, t_pos *pos, char **map)
{	
	if (map[act.act_y + 1][act.act_x] != '1'
		&& map[act.act_y + 1][act.act_x] != '2')
	{
		pos[*top].y = act.act_y + 1;
		pos[*top].x = act.act_x;
		if (should_i_be_here(1, act, map, data) == 1 /*map[act.act_y + 1][act.act_x] == 'E'*/)
			return (1);
		map[act.act_y + 1][act.act_x] = '2';
		++*top;
	}
	if (map[act.act_y - 1][act.act_x] != '1'
		&& map[act.act_y - 1][act.act_x] != '2')
	{
		pos[*top].y = act.act_y - 1;
		pos[*top].x = act.act_x;
		if (should_i_be_here(2, act, map, data) == 1  /*map[act.act_y - 1][act.act_x] == 'E'*/)
			return (1);
		map[act.act_y - 1][act.act_x] = '2';
		++*top;
	}
	return (0);
}

int	try_left_right(t_data *data, t_actpos act, int *top, t_pos *pos, char **map)
{
	if (map[act.act_y][act.act_x + 1] != '1'
		&& map[act.act_y][act.act_x + 1] != '2')
	{
		pos[*top].y = act.act_y;
		pos[*top].x = act.act_x + 1;
		if (should_i_be_here(3, act, map, data) == 1 /*map[act.act_y][act.act_x + 1] == 'E'*/)
			return (1);
		map[act.act_y][act.act_x + 1] = '2';
		++*top;
	}
	if (map[act.act_y][act.act_x - 1] != '1'
		&& map[act.act_y][act.act_x - 1] != '2')
	{
		pos[*top].y = act.act_y;
		pos[*top].x = act.act_x - 1;
		if (should_i_be_here(4, act, map, data) == 1 /*map[act.act_y][act.act_x - 1] == 'E'*/)
			return (1);
		map[act.act_y][act.act_x - 1] = '2';
		++*top;
	}
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
	int			top;
	t_pos		pos[1024];
	t_actpos	act;
	char		**map;
	

	map = duplicata_map(data);
	if (!map)
		return (1);
	top = 1;
	act.act_x = 0;
	act.act_y = 0;
	pos[0].x = data->player.IntposX;
	pos[0].y = data->player.IntposY;
	while (top > 0)
	{
		//print_tab(map);
		//printf("-------------------------------------------\n           on bottom timeline\n-------------------------------------------\n");
		top--;
		act.act_x = pos[top].x;
		act.act_y = pos[top].y;
		if (try_up_down(data, act, &top, pos, map) == 1)
			return (path_free_map(data, map), 1);
		if (try_left_right(data, act, &top, pos, map) == 1)
			return (path_free_map(data, map), 1);
	}
	path_free_map(data, map);
	return (0);
}

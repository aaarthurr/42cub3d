/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leoherna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:20:42 by arpages           #+#    #+#             */
/*   Updated: 2024/04/24 16:14:52 by leoherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	get_all(char **argv, t_data *data)
{
	if (check_file(argv[1]))
		return;
	data->map_info.map_path = argv[1];
    copy_file(&data->map_info);
    get_map(&data->map_info);
}


/* this funtiom copy a file gave in struct map_info->map_path
	in the variable char **global */
void	copy_file(t_map_info *map_info)
{
	int		fd;
	int		j;
	char	*temp;

	j = 0;
	map_info->height = 0;
	fd = open(map_info->map_path, O_RDWR);
	temp = get_next_line(fd);
	while (temp != NULL)
	{
		free(temp);
		map_info->height++;
		temp = get_next_line(fd);
	}
	free(temp);
	close(fd);
	map_info->global = malloc(sizeof(char *) * (map_info->height + 1));
	fd = open(map_info->map_path, O_RDWR);
	while (j < map_info->height)
	{
		map_info->global[j] = get_next_line(fd);
		j++;
	}
	map_info->global[j] = NULL;
	close(fd);
}

/* this fontion create a char ** with only the map part contained in the file*/
void get_map(t_map_info *map_info)
{
	int i;
	char **map;

	map = NULL;
	i = map_info->height;
	while (is_map_part(map_info->global[i]) == 0)
		i--;
	while (is_map_part(map_info->global[i]) == 1)
	{
		map = tab_realloc(map, 1, map_info->global[i]);
		i--;
	}
	map_info->map = map;
}


/* checke if the line contain part of a map*/
int is_map_part(char *line)
{
	int i;

	i = 0;
	if (line == NULL)
		return (0);
	while(line[i] != '\0')
	{
		if (line[i] == '1')
			return (1);
		i++;
	}
	return (0);
}

void set_pos(t_data *data, int x, int y)
{
	data->player.posX = (double)x + 0.5;
	data->player.posY = (double)y + 0.5;
}
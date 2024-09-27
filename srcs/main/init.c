/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leoherna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:20:42 by arpages           #+#    #+#             */
/*   Updated: 2024/09/26 19:42:32 by leoherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	get_all(char **argv, t_data *data)
{
	if (check_file(argv[1]) )
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
	fd = open(map_info->map_path, O_RDONLY);
	temp = get_next_line(fd);
	while (temp != NULL)
	{
		free(temp);
		map_info->height = map_info->height + 1;
		temp = get_next_line(fd);
	}
	free(temp);
	close(fd);
	map_info->global = malloc(sizeof(char *) * (map_info->height + 1));
	fd = open(map_info->map_path, O_RDONLY);
	while (j < map_info->height)
	{
		map_info->global[j] = get_next_line(fd);
		printf("line : [%s]\n", map_info->global[j]);
		j++;
	}
	map_info->global[j] = NULL;
	map_info->global_len = j;
	close(fd);
}

/* this fontion create a char ** with only the map part contained in the file*/
void	get_map(t_map_info *map_info)
{
	int size;
	int i;
	int j = -1;
	char **map;

	
	map = NULL;
	i = 0;
	size = map_info->height;
	while (is_map_part(map_info->global[i]) == 0 && i < size)
		i++;
	while (is_map_part(map_info->global[i]) == 1 && i < size)
	{
		if (j == -1)
			j = i;
		//map = tab_realloc(map, 1, map_info->global[i]);
		i++;
	}
	map = malloc(sizeof(char *) * ((i - j) + 1));
	i = 0;
	while (is_map_part(map_info->global[j]) == 1 && j < size)
	{
		printf("--------------\n");
		map[i] = ft_strdup(map_info->global[j]);
		printf("--------------\n");
		j++;
		i++;
	}
	map[i] = NULL;
	get_next_line(-1);
	map_info->map = map;
}


/* checke if the line contain part of a map*/
int is_map_part(char *line)
{
	int i;

	i = 0;
	if (line == NULL)
		return (0);
	while(line[i] != '\0' && ft_strchr(line[i], " 10NSEW") == 1)
	{
		if (line[i] == '1')
			return (1);
		i++;
	}
	return (0);
}

void	set_pos(t_data *data, int x, int y, char dir)
{
	data->player.IntposX = x;
	data->player.IntposY = y;
	data->player.posX = ((double)x) + 0.5;
	data->player.posY = ((double)y)+ 0.5;
	
	if (dir == 'S')
		set_vector(data, 0, 1);
	else if (dir == 'N')
		set_vector(data, 0, -1);
	else if (dir == 'E')
		set_vector(data, 1, 0);
	else if (dir == 'W')
		set_vector(data, -1, 0);
}

void	set_vector(t_data *data, int x, int y)
{
	data->player.dirX = x;
	data->player.dirY = y;
	data->player.planX = y * -0.70;
	data->player.planY = x * 0.70;
	data->player.speed = 50;
	data->player.jump_speed = 0.02;
	data->player.posZ = 0.65;
	data->player.is_falling = 0;
	data->player.is_jumping = 0;
	data->player.walk_phase = 1;
}

void	set_keys(t_data *data)
{
	data->key_info.key_w = 0;
	data->key_info.key_a = 0;
	data->key_info.key_s = 0;
	data->key_info.key_d = 0;
	data->key_info.key_left = 0;
	data->key_info.key_right = 0;
	data->key_info.key_esc = 0;
	data->key_info.key_jump = 0;
}
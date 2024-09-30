/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arpages <arpages@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:20:42 by arpages           #+#    #+#             */
/*   Updated: 2024/09/30 16:04:16 by arpages          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	get_all(char **argv, t_data *data)
{
	if (check_file(argv[1]))
		return ;
	data->map_info.map_path = argv[1];
	copy_file(&data->map_info);
	get_map(&data->map_info);
}

void	copy_file(t_map_info *map_info)
{
	t_var	var;

	var.j = 0;
	map_info->height = 0;
	var.fd = open(map_info->map_path, O_RDONLY);
	var.temp = get_next_line(var.fd);
	while (var.temp != NULL)
	{
		free(var.temp);
		map_info->height = map_info->height + 1;
		var.temp = get_next_line(var.fd);
	}
	free(var.temp);
	close(var.fd);
	map_info->global = malloc(sizeof(char *) * (map_info->height + 1));
	var.fd = open(map_info->map_path, O_RDONLY);
	while (var.j < map_info->height)
	{
		map_info->global[var.j] = get_next_line(var.fd);
		var.j++;
	}
	map_info->global[var.j] = NULL;
	map_info->global_len = var.j;
	close(var.fd);
}

void	get_map(t_map_info *map_info)
{
	t_var	var;

	var.tab = NULL;
	var.j = -1;
	var.i = 0;
	var.size = map_info->height;
	while (is_map_part(map_info->global[var.i]) == 0 && var.i < var.size)
		var.i++;
	while (is_map_part(map_info->global[var.i]) == 1 && var.i < var.size)
	{
		if (var.j == -1)
			var.j = var.i;
		var.i++;
	}
	var.tab = malloc(sizeof(char *) * ((var.i - var.j) + 1));
	var.i = 0;
	while (is_map_part(map_info->global[var.j]) == 1 && var.j < var.size)
	{
		var.tab[var.i] = ft_strdup(map_info->global[var.j]);
		var.j++;
		var.i++;
	}
	var.tab[var.i] = NULL;
	get_next_line(-1);
	map_info->map = var.tab;
}

int	is_map_part(char *line)
{
	int	i;

	i = 0;
	if (line == NULL)
		return (0);
	while (line[i] != '\0' && ft_strchr(line[i], " 10NSEW") == 1)
	{
		if (line[i] == '1')
			return (1);
		i++;
	}
	return (0);
}

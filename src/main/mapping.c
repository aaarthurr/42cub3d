/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arpages <arpages@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 14:12:26 by arpages           #+#    #+#             */
/*   Updated: 2024/04/22 17:29:13 by arpages          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

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

/* classic realloc funtion*/
char **tab_realloc(char **tab, int m_size, char *content)
{
	int i;
	char **new_tab;

	i = 0;
	new_tab = malloc(sizeof(char *) * (tab_size(tab) + m_size + 1));
	while (tab != NULL && tab[i] != NULL)
	{
		new_tab[i] = tab[i];
		i++;
	}
	while(i < (tab_size(tab) + m_size))
	{
		new_tab[i] = content;
		i++;
	}
	new_tab[i] = NULL;
	if (tab != NULL)
		free(tab);
	return(new_tab);
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

/*return size of a tab*/
int tab_size(char **tab)
{
	int i;

	i = 0;
	if(tab == NULL)
		return (0);
	while (tab[i] != NULL)
		i++;
	return (i);
}
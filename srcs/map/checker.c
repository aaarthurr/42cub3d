/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leoherna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:21:00 by arpages           #+#    #+#             */
/*   Updated: 2024/09/28 15:23:23 by leoherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

int	check_map(t_data *data)
{
	if (data->map_info.height > 300)
	{
		printf("Error unvalid map : Too Huge (Like ya cock buddy)\n");
		return (free_line(data), 1);
	}
	if (check_walls(data) == 1)
	{
		printf("Error unvalid map : Unrecognized charset\n");
		return (free_line(data), 1);
	}
	if (path_finding(data) == 1)
	{
		printf("Error unvalid map : Unfinished walls\n");
		return (free_line(data), 1);
	}
	return (0);
}

int	check_path_cub_file(char *str)
{
	int	i;

	if (str == NULL)
		return (1);
	i = ft_strlen(str);
	while (i > 0)
	{
		i--;
		if (str[i] == '.')
			break ;
	}
	if ((str[i + 1] != '\0' && str[i + 1] == 'c')
		&& (str[i + 2] != '\0' && str[i + 2] == 'u')
		&& (str[i + 3] != '\0' && str[i + 3] == 'b')
		&& str[i + 4] == '\0')
		return (0);
	return (1);
}

int	check_file(char *str)
{
	int	fd;

	if (check_path_cub_file(str) == 1)
	{
		error_manager("file name should end with .cub", 101);
		return (1);
	}
	fd = open(str, O_RDONLY);
	if (fd == -1)
	{
		error_manager("Error while opening file", 102);
		return (1);
	}
	close(fd);
	return (0);
}

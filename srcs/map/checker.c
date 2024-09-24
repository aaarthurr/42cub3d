/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leoherna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:21:00 by arpages           #+#    #+#             */
/*   Updated: 2024/09/24 16:09:16 by leoherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

int check_map(t_data *data)
{
    //print_tab(data.map_info.map);
	if (check_elements(data) == 1)
    {
        printf("Error unvalid map : Unrecognized charset\n");
		return (1);
    }
    if (check_walls(data) == 1)
    {
        printf("Error\n");
		return (1);
    }
	if (path_finding(data) == 1)
    {
        printf("Error unvalid map : Unfinished walls\n");
		return (1);
    }
    return (0);
}

int check_file(char *str)
{
	int i;

	i = ft_strlen(str);
	if (ft_strncmp(str + (i - 4), ".cub", 4) != 0)
	{
		error_manager("file name should end with .cub", 101);
		return(1);
	}
	i = open(str, O_RDONLY);
	if (i == -1)
	{
		error_manager("Error while opening file", 102);
		return(1);
	}
	close(i);
	return (0);
}
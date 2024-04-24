/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leoherna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:21:00 by arpages           #+#    #+#             */
/*   Updated: 2024/04/24 16:26:40 by leoherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

int check_map(t_data *data)
{
    //print_tab(data.map_info.map);
    if (check_walls(data) == 1)
    {
        printf("error\n");
    }
   	printf("%f . %f\n", data->player.posX, data->player.posY);
    return (0);
}

int check_file(char *str)
{
	int i;

	i = ft_strlen(str);
	if (ft_strncmp(str + (i - 4), ".cub", 4) != 0)
		error_manager("file name should end with .cub", 101);
	i = open(str, O_RDONLY);
	if (i == -1)
		error_manager("Error while opening file", 102);
	close(i);
	return (0);
}
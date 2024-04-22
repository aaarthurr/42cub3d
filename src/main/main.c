/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arpages <arpages@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:04:05 by arpages           #+#    #+#             */
/*   Updated: 2024/04/22 17:27:53 by arpages          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

int main(int argc, char **argv)
{
    t_map_info *map_info;
    t_data data;
  
    map_info = malloc(sizeof(t_map_info));
    if (argc != 2)
        printf("only argument is the map path\n");
    else
    {
        data.map_info.map_path = argv[1];
        copy_file(&data.map_info);
        //print_tab(data.map_info.global);
        get_map(&data.map_info);
        print_tab(data.map_info.map);
    }
        
}

void	print_tab(char **tab)
{
	int		i;

	i = 0;
	while (tab[i] != NULL)
	{
        printf("%s\n", tab[i]);
		i++;
	}
}
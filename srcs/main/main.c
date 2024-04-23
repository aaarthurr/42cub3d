/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arpages <arpages@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:04:05 by arpages           #+#    #+#             */
/*   Updated: 2024/04/23 13:10:31 by arpages          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

int main(int argc, char **argv)
{
    t_data data;

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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arpages <arpages@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:04:05 by arpages           #+#    #+#             */
/*   Updated: 2024/04/25 14:08:42 by arpages          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

int main(int argc, char **argv)
{
    t_data data;

    if (argc < 2)
    {
        printf("Mettez map : %s\n", argv[0]);
    }
    else
    {
        get_all(argv, &data);
        check_map(&data);
		game_manager(&data);
    }
	return (0);
}




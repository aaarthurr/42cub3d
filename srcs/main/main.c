/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leoherna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:04:05 by arpages           #+#    #+#             */
/*   Updated: 2024/09/23 13:39:35 by leoherna         ###   ########.fr       */
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
        if (check_map(&data) == 0)
	    {
            set_keys(&data);
		    game_manager(&data);
        }
    }
	return (0);
}

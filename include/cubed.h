/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubed.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arpages <arpages@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:03:08 by arpages           #+#    #+#             */
/*   Updated: 2024/04/22 15:20:54 by arpages          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBED_H
# define CUBED_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include "cubed.h"

typedef struct map_info_s
{
    char *map_path;
    char **global;
    char **info;
    char **map;
    int height;
}               t_map_info;

typedef struct data_s
{
    t_map_info  map_info;
}				t_data;



#endif
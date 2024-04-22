/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubed.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arpages <arpages@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:03:08 by arpages           #+#    #+#             */
/*   Updated: 2024/04/22 17:28:00 by arpages          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBED_H
# define CUBED_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>

# include "get_next_line.h"

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


void    copy_file(t_map_info *map_info);
void    get_map(t_map_info *map_info);
char    **tab_realloc(char **tab, int m_size, char *content);
int     is_map_part(char *line);
int     tab_size(char **tab);

void	print_tab(char **tab);

#endif
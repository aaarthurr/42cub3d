/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leoherna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 14:12:26 by arpages           #+#    #+#             */
/*   Updated: 2024/09/24 16:59:27 by leoherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

int check_path(t_data *data)
{
    int fd;
    
    fd = open(data->texture.Ewall_path, O_RDONLY);
    if (fd == -1)
        return(1);
    fd = open(data->texture.Wwall_path, O_RDONLY);
    if (fd == -1)
        return(1);
    fd = open(data->texture.Nwall_path, O_RDONLY);
    if (fd == -1)
        return(1);
    fd = open(data->texture.Swall_path, O_RDONLY);
    if (fd == -1)
        return(1);
    return(0);
}

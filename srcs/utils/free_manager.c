/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leoherna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:57:52 by leoherna          #+#    #+#             */
/*   Updated: 2024/04/24 14:57:52 by leoherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void    free_mapinfo(t_data *data)
{
    free_tab(data->map_info.global);
    free_tab(data->map_info.map);
    free_tab(data->map_info.info);
    //free(&data->map_info.map_path)

}
void    free_tab(char **tab)
{
        size_t  i;

        i = 0;
        while (tab[i])
        {
                free(tab[i]);
                i++;
        }
        free(tab);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_bis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arpages <arpages@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 15:21:58 by arthur            #+#    #+#             */
/*   Updated: 2024/09/30 16:06:29 by arpages          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	generate_path_bis(t_data *data, t_var *var, int index)
{
	while (data->map_info.global[index][var->i] != '\0'
			&& data->map_info.global[index][var->i] == ' ')
		var->i++;
	while (data->map_info.global[index][var->i] != '\n'
			&& data->map_info.global[index][var->i] != '\0')
	{
		var->size++;
		var->i++;
	}
	var->temp = malloc(sizeof(char) * (var->size + 1));
	var->i = var->i - var->size;
	while (data->map_info.global[index][var->i] != '\n'
			&& data->map_info.global[index][var->i] != '\0')
	{
		var->temp[var->j] = data->map_info.global[index][var->i];
		var->i++;
		var->j++;
	}
	var->temp[var->j] = '\0';
}

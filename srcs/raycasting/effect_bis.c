/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   effect_bis.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leoherna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 18:30:00 by leoherna          #+#    #+#             */
/*   Updated: 2024/09/25 18:30:00 by leoherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	death(t_data *data, const char *str)
{
	printf("%s\n", str);
	close_window(data);
}

void	take_drugs(t_data *data)
{
	if (data->player.drug_level == 0)
		data->player.drug_time = get_current_time() + 60000;
	data->player.drug_level++;
}

int	give_lsd(t_data *data, int color)
{
	double	modifier;

	if (data->player.color_phase < 250)
		return (color + data->player.color_phase);
	modifier = (double)((get_current_time() / 100) % 200) / 100;
	return (color * modifier);
}

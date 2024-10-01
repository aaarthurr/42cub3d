/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   effect.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leoherna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 18:30:00 by leoherna          #+#    #+#             */
/*   Updated: 2024/09/25 18:30:00 by leoherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	shake_screen(t_data *data)
{
	double	x;

	x = (rand() % 11);
	x = x / 3000;
	if (data->player.shake_phase == 10)
		data->player.shake_phase = -10;
	if (data->player.shake_phase >= 0)
	{
		data->player.posz += x;
		data->player.shake_phase += 1;
	}
	else if (data->player.shake_phase < 0)
	{
		data->player.posz -= x;
		data->player.shake_phase += 1;
	}
}

void	parasite_screen(t_data *data)
{
	int	i;
	int	x;
	int	y;
	int	bw;

	i = 0;
	while (i < 400)
	{
		x = rand() % data->win_width;
		y = rand() % data->win_height;
		bw = rand() % 2;
		if (bw == 0)
			pixel_put_opti(&(data->img), x, y, 0xFFFFFF);
		else
			pixel_put_opti(&(data->img), x, y, 0x000000);
		i++;
	}
}

void	fuck_fov(t_data *data)
{
	if (data->player.fov_phase >= 300)
		data->player.fov_phase = -300;
	if (data->player.fov_phase >= 0)
	{
		data->player.planx -= 0.01;
		data->player.plany += 0.01;
		data->player.fov_phase += rand() % 10;
	}
	else if (data->player.fov_phase < 0)
	{
		data->player.planx += 0.01;
		data->player.plany -= 0.01;
		data->player.fov_phase += rand() % 10;
	}
}

void	give_effect(t_data *data)
{
	if (data->player.drug_level > 0)
		shake_screen(data);
	if (data->player.drug_level > 2)
		parasite_screen(data);
	if (data->player.drug_level > 6)
		fuck_fov(data);
	if (data->player.color_phase < 250 && data->player.drug_level >= 5)
		data->player.color_phase++;
}

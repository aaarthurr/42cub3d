/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_movement.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leoherna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 17:55:11 by leoherna          #+#    #+#             */
/*   Updated: 2024/09/23 17:55:11 by leoherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

int	set_mouse_center_screen(t_data *data)
{
	data->mouse.origin_x = (data->win_width / 2);
	data->mouse.origin_y = (data->win_height / 2);
	mlx_mouse_move(data->mlx, data->win,
		data->mouse.origin_x, data->mouse.origin_y);
	return (0);
}

int	mouse_move(int x, int y, t_data *data)
{
	int		x_distance;
	double	rot_coef;
	double	sensibilite;

	(void)y;
	x_distance = 0;
	sensibilite = 1000;
	if (x < (data->win_width / 2))
		x_distance = x - (data->win_width / 2);
	else if (x > (data->win_width / 2))
		x_distance = x - (data->win_width / 2);
	rot_coef = (double)x_distance / sensibilite;
	if (data->mouse.mouse_lock == 1)
	{
		rotate_player(data, rot_coef);
		set_mouse_center_screen(data);
	}
	return (0);
}

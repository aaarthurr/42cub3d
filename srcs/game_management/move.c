/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arpages <arpages@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 15:22:13 by arpages           #+#    #+#             */
/*   Updated: 2024/09/30 15:49:38 by arpages          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	move_player(t_data *data, int x, int y)
{
	double	prev_x;
	double	prev_y;

	prev_x = data->player.posx;
	prev_y = data->player.posy;
	data->player.posx += (data->player.dirx * x) / data->player.speed;
	data->player.posy += (data->player.diry * x) / data->player.speed;
	data->player.posx += (data->player.diry * -y) / data->player.speed;
	data->player.posy += (data->player.dirx * y) / data->player.speed;
	if (data->map_info.map[(int)(data->player.posy)][(int)prev_x] == '1')
		data->player.posy = prev_y;
	if (data->map_info.map[(int)prev_y][(int)(data->player.posx)] == '1')
		data->player.posx = prev_x;
	walk_height(data);
}

void	walk_height(t_data *data)
{
	if (data->key_info.key_jump == 1)
		return ;
	else if (data->player.walk_phase == 1)
	{
		if (data->player.posz >= 0.658)
			data->player.walk_phase = -1;
		data->player.posz += (0.05 / data->player.speed);
	}
	else if (data->player.walk_phase == -1)
	{
		if (data->player.posz <= 0.642)
			data->player.walk_phase = 1;
		data->player.posz -= (0.05 / data->player.speed);
	}
}

void	jump(t_data *data)
{
	if (data->player.jump_speed < 0.001)
		data->player.jump_speed = 0.001;
	if (data->player.posz > 0.25 && data->player.is_falling == 0)
	{
		data->player.posz -= data->player.jump_speed;
		data->player.jump_speed -= 0.0005;
		if (data->player.posz <= 0.25)
		{
			data->player.is_falling = 1;
		}
	}
	else if (data->player.posz < 0.65)
	{
		data->player.posz += data->player.jump_speed;
		data->player.jump_speed += 0.0005;
		if (data->player.posz >= 0.65)
		{
			data->player.posz = 0.65;
			data->player.is_falling = 0;
			data->key_info.key_jump = 0;
			data->player.jump_speed = 0.02;
		}
	}
}

void	rotate_player(t_data *data, double angle)
{
	double	c_x;
	double	c_y;

	c_x = data->player.dirx;
	c_y = data->player.diry;
	data->player.dirx = (c_x * cos(angle)) - (c_y * sin(angle));
	data->player.diry = (c_x * sin(angle)) + (c_y * cos(angle));
	c_x = data->player.planx;
	c_y = data->player.plany;
	data->player.planx = (c_x * cos(angle)) - (c_y * sin(angle));
	data->player.plany = (c_x * sin(angle)) + (c_y * cos(angle));
}

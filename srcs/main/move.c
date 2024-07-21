/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arpages <arpages@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 15:22:13 by arpages           #+#    #+#             */
/*   Updated: 2024/07/20 16:26:50 by arpages          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void move_player(t_data *data, int x, int y)
{
	double prev_x;
	double prev_y;

	prev_x = data->player.posX;
	prev_y = data->player.posY;
	data->player.posX += (data->player.dirX * x) / data->player.speed;
	data->player.posY += (data->player.dirY * x) / data->player.speed;
	data->player.posX += (data->player.dirY * -y) / data->player.speed;
	data->player.posY += (data->player.dirX * y) / data->player.speed;
	if (data->map_info.map[(int)(data->player.posY)][(int)prev_x] == '1')
		data->player.posY = prev_y;
	if (data->map_info.map[(int)prev_y][(int)(data->player.posX)] == '1')
		data->player.posX = prev_x;
	walk_height(data);
}

void	walk_height(t_data *data)
{
	if (data->key_info.key_jump == 1)
		return ;
	else if (data->player.walk_phase == 1)
	{
		if (data->player.posZ >= 0.658)
			data->player.walk_phase = -1;
		data->player.posZ += (0.05 / data->player.speed);
	}
	else if (data->player.walk_phase == -1)
	{
		if (data->player.posZ <= 0.642)
			data->player.walk_phase = 1;
		data->player.posZ -= (0.05 / data->player.speed);
	}
}

void	jump(t_data *data)
{
	if (data->player.jump_speed < 0.001)
		data->player.jump_speed = 0.001;
	printf("%f - %f - %d\n", data->player.posZ, data->player.jump_speed, data->player.is_falling);
	if (data->player.posZ > 0.25 && data->player.is_falling == 0)
	{
		data->player.posZ -= data->player.jump_speed;
		data->player.jump_speed -= 0.0005;
		if (data->player.posZ <= 0.25)
		{
			data->player.is_falling = 1;
		}
	}
	else if (data->player.posZ < 0.65)
	{
		data->player.posZ += data->player.jump_speed;
		data->player.jump_speed += 0.0005;
		if (data->player.posZ >= 0.65)
		{
			data->player.posZ = 0.65;
			data->player.is_falling = 0;
			data->key_info.key_jump = 0;
			data->player.jump_speed = 0.02;
		}
	}
}

void rotate_player(t_data *data, double angle)
{
	double c_x;
	double c_y;

	c_x = data->player.dirX;
	c_y = data->player.dirY;
	data->player.dirX = (c_x * cos(angle)) - (c_y * sin(angle));
	data->player.dirY = (c_x * sin(angle)) + (c_y * cos(angle));
	c_x = data->player.planX;
	c_y = data->player.planY;
	data->player.planX = (c_x * cos(angle)) - (c_y * sin(angle));
	data->player.planY = (c_x * sin(angle)) + (c_y * cos(angle));
}

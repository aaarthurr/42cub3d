/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arpages <arpages@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:20:42 by arpages           #+#    #+#             */
/*   Updated: 2024/09/30 16:04:16 by arpages          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	set_pos(t_data *data, int x, int y, char dir)
{
	data->player.intposx = x;
	data->player.intposy = y;
	data->player.posx = ((double)x) + 0.5;
	data->player.posy = ((double)y) + 0.5;
	if (dir == 'S')
		set_vector(data, 0, 1);
	else if (dir == 'N')
		set_vector(data, 0, -1);
	else if (dir == 'E')
		set_vector(data, 1, 0);
	else if (dir == 'W')
		set_vector(data, -1, 0);
}

void	set_vector(t_data *data, int x, int y)
{
	data->player.dirx = x;
	data->player.diry = y;
	data->player.planx = y * -0.70;
	data->player.plany = x * 0.70;
	data->player.speed = 50;
	data->player.jump_speed = 0.02;
	data->player.posz = 0.65;
	data->player.is_falling = 0;
	data->player.is_jumping = 0;
	data->player.walk_phase = 1;
}

void	set_keys(t_data *data)
{
	data->key_info.key_w = 0;
	data->key_info.key_a = 0;
	data->key_info.key_s = 0;
	data->key_info.key_d = 0;
	data->key_info.key_left = 0;
	data->key_info.key_right = 0;
	data->key_info.key_esc = 0;
	data->key_info.key_jump = 0;
}

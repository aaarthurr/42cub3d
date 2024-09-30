/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_manager_bis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arpages <arpages@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 15:09:55 by arpages           #+#    #+#             */
/*   Updated: 2024/09/30 15:20:23 by arpages          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

#define GRID_SIZE 20
#define KEY_CTRL 65507
#define KEY_ESC 65307
#define KEY_A 100
#define KEY_D 97
#define KEY_S 115
#define KEY_W 119
#define KEY_E 101
#define KEY_L 108
#define KEY_SPACE_BAR 32
#define KEY_LEFT 65361
#define KEY_RIGHT 65363
#define KEY_SHIFT 65505
#define CELL_SIZE 50

void	key_pressed_bis(int keycode, t_data *data)
{
	if (keycode == KEY_SHIFT)
		data->player.speed = 20;
	if (keycode == KEY_SPACE_BAR)
		data->key_info.key_jump = 1;
	if (keycode == KEY_CTRL)
	{
		if (data->mouse.mouse_lock == 1)
			data->mouse.mouse_lock = 0;
		else
			data->mouse.mouse_lock = 1;
	}
}

void	multi_key_bis(t_data *data)
{
	size_t	frame_time;
	int		frame_lenght;
	int		fps;

	frame_lenght = get_current_time() - data->last_frame;
	if (frame_lenght < 10)
		usleep((10 - frame_lenght) * 1000);
	frame_time = get_current_time();
	fps = 1000 / (frame_time - data->last_frame);
	data->last_frame = frame_time;
	if (data->player.drug_time != -1
		&& (size_t)(data->player.drug_time) < get_current_time())
		death(data, "You passed out... Game Over");
	if (data->player.drug_level == 10)
		death(data, "You did an Overdose... Victory");
}

int	key_pressed(int keycode, t_data *data)
{
	if (keycode == KEY_ESC)
		data->key_info.key_esc = 1;
	if (keycode == KEY_S)
		data->key_info.key_s = 1;
	if (keycode == KEY_W)
		data->key_info.key_w = 1;
	if (keycode == KEY_A)
		data->key_info.key_a = 1;
	if (keycode == KEY_D)
		data->key_info.key_d = 1;
	if (keycode == KEY_L)
		take_drugs(data);
	if (keycode == KEY_RIGHT)
		data->key_info.key_right = 1;
	if (keycode == KEY_LEFT)
		data->key_info.key_left = 1;
	key_pressed_bis(keycode, data);
	return (0);
}

int	key_released(int keycode, t_data *data)
{
	if (keycode == KEY_ESC)
		data->key_info.key_esc = 0;
	if (keycode == KEY_S)
		data->key_info.key_s = 0;
	if (keycode == KEY_W)
		data->key_info.key_w = 0;
	if (keycode == KEY_A)
		data->key_info.key_a = 0;
	if (keycode == KEY_D)
		data->key_info.key_d = 0;
	if (keycode == KEY_RIGHT)
		data->key_info.key_right = 0;
	if (keycode == KEY_LEFT)
		data->key_info.key_left = 0;
	if (keycode == KEY_SHIFT)
		data->player.speed = 40;
	return (0);
}

int	multi_key(t_data *data)
{
	if (data->key_info.key_esc == 1)
		close_window(data);
	if (data->key_info.key_s == 1)
		move_player(data, -1, 0);
	if (data->key_info.key_w == 1)
		move_player(data, 1, 0);
	if (data->key_info.key_a == 1)
		move_player(data, 0, 1);
	if (data->key_info.key_d == 1)
		move_player(data, 0, -1);
	if (data->key_info.key_left == 1)
		rotate_player(data, -0.02);
	if (data->key_info.key_right == 1)
		rotate_player(data, 0.02);
	if (data->key_info.key_jump == 1)
		jump(data);
	multi_key_bis(data);
	send_rays(data);
	return (0);
}

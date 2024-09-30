/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arpages <arpages@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:29:44 by leoherna          #+#    #+#             */
/*   Updated: 2024/09/30 15:15:41 by arpages          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

int	close_window(t_data *data)
{
	free_function(data);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit(0);
}

void	ft_test(t_data *data)
{
	mlx_hook(data->win, 2, 1L << 0, key_pressed, data);
	mlx_hook(data->win, 3, 1L << 1, key_released, data);
	mlx_hook(data->win, 6, (1L << 6), mouse_move, data);
	mlx_hook(data->win, 17, 0, close_window, data);
	mlx_loop_hook(data->mlx, multi_key, data);
	mlx_loop(data->mlx);
}

int	game_manager(t_data *data)
{
	data->player.drug_time = -1;
	data->win_height = 500;
	data->win_width = 700;
	data->mouse.mouse_lock = ACTIVATE_MOUSE;
	data->player.drug_level = 0;
	data->player.shake_phase = 5;
	data->player.fov_phase = 150;
	data->player.color_phase = 0;
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, data->win_width, data->win_height,
			"OVERDOSE SIMULATOR : Backroom edition");
	generate_base_img(data);
	get_image(data);
	create_image(data);
	data->last_frame = get_current_time();
	set_sprite(data, 20);
	send_rays(data);
	ft_test(data);
	return (0);
}

void	generate_base_img(t_data *data)
{
	data->img.img_ptr = mlx_new_image(data->mlx, data->win_width,
			data->win_height);
	data->img.img_char = mlx_get_data_addr(data->img.img_ptr,
			&(data->img.bits_pix), &(data->img.len), &(data->img.endian));
}

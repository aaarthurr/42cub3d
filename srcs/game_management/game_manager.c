/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leoherna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:29:44 by leoherna          #+#    #+#             */
/*   Updated: 2024/09/30 10:56:38 by leoherna         ###   ########.fr       */
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

int     close_window(t_data *data)
{   
    free_function(data);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
    exit(0);
}

int	key_pressed(int keycode, t_data *data)
{
	
	// keycode = 108 pour L
	//keycode = 101 pour E
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
	size_t	frame_time;
	int		frame_lenght;
	int		fps;
	
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
		
	
	
	
	//ajouter souris
		
	if (data->key_info.key_jump == 1)
		jump(data);
    send_rays(data);
	frame_lenght = get_current_time() - data->last_frame;
	if (frame_lenght < 10)
	 	usleep((10 - frame_lenght) * 1000);
	frame_time = get_current_time();
	fps = 1000 / (frame_time - data->last_frame);
	data->last_frame = frame_time;
	if (data->player.drug_time != -1 && (size_t)(data->player.drug_time) < get_current_time())
		death(data, "You passed out... Game Over");
	if (data->player.drug_level == 10)
		death(data, "You did an Overdose... Victory");
    return (0);
}

void ft_test(t_data *data)
{
	mlx_hook(data->win, 2, 1L << 0, key_pressed, data);	
	mlx_hook(data->win, 3, 1L << 1, key_released, data);
	mlx_hook(data->win, 6, (1L << 6), mouse_move, data);
	mlx_hook(data->win, 17, 0, close_window, data);
	mlx_loop_hook(data->mlx, multi_key, data);
	mlx_loop(data->mlx);
}


int     game_manager(t_data *data)
{
	//500 / 700
	data->player.drug_time = -1;
	data->win_height = 500;
	data->win_width = 700;
	data->mouse.mouse_lock = ACTIVATE_MOUSE;
	data->player.drug_level = 0;
	data->player.shake_phase = 5;
	data->player.fov_phase = 150;
	data->player.color_phase = 0;
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, data->win_width, data->win_height, "OVERDOSE SIMULATOR : Backroom edition");
	generate_base_img(data);
	get_image(data);
	create_image(data);
	printf("%d\n",tab_size(data->map_info.map));
	data->last_frame = get_current_time();
	set_sprite(data, 20);
	send_rays(data);
	//mlx_mouse_hook(data->win, mouse_move, &data);
	ft_test(data);
    return (0);
}

void	generate_base_img(t_data *data)
{
	data->img.img_ptr = mlx_new_image(data->mlx, data->win_width, data->win_height);
	data->img.img_char = mlx_get_data_addr(data->img.img_ptr, &(data->img.bits_pix), &(data->img.len), &(data->img.endian));
	//printf("INFO -> %d, %d ,%d\n", data->img.len, data->img.bits_pix, data->img.endian);
}

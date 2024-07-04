/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:29:44 by leoherna          #+#    #+#             */
/*   Updated: 2024/07/04 17:37:31 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cubed.h"

#define GRID_SIZE 20
#define KEY_ESC 65307
#define KEY_A 100
#define KEY_D 97
#define KEY_S 115
#define KEY_W 119
#define KEY_SPACE_BAR 32
#define KEY_LEFT 65361
#define KEY_RIGHT 65363
#define KEY_SHIFT 65505
#define CELL_SIZE 50

int     close_window(t_data *data)
{
        //free_player(data);
        free_mapinfo(data);
        mlx_destroy_window(data->mlx, data->win);
        mlx_destroy_display(data->mlx);
        free(data->mlx);
        exit(0);
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
	if (keycode == KEY_RIGHT)
		data->key_info.key_right = 1;
	if (keycode == KEY_LEFT)
		data->key_info.key_left = 1;
	if (keycode == KEY_SHIFT)
	 	data->player.speed = 10;
	if (keycode == KEY_SPACE_BAR)
	 	data->key_info.key_jump = 1;
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
	 	data->player.speed = 50;
	return (0);
}

void ft_test_pix(t_data *data)
{
    // Boucle extérieure : 64 itérations
    for (int i = 0; i < 64; i++) {
        // Boucle intérieure : 64 itérations
        for (int j = 0; j < 64; j++) {
            // Ici, vous pouvez insérer le code que vous souhaitez exécuter à chaque itération
			pixel_put_opti(&data->img, i, j, get_pixel_color(&data->texture.wall, i, j));
            printf("i = %d, j = %d\n", i, j);
        }
    }
	
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
		move_player(data, 0, -1);
	if (data->key_info.key_d == 1)
		move_player(data, 0, 1);
	if (data->key_info.key_left == 1)
		rotate_player(data, 0.02);
	if (data->key_info.key_right == 1)
		rotate_player(data, -0.02);
	if (data->key_info.key_jump == 1)
		jump(data);
    send_rays(data);
	frame_lenght = get_current_time() - data->last_frame;
	if (frame_lenght < 10)
		usleep((10 - frame_lenght) * 1000);
	frame_time = get_current_time();
	fps = 1000 / (frame_time - data->last_frame);
	data->last_frame = frame_time;
	printf("fps -> %d\n", fps);
	//mlx_string_put(data->mlx, data->win, 10, 10, 0xFFFFFF, ft_itoa(fps));
	//printf("%f , %f [%f, %f]\n", data->player.posX, data->player.posY, data->player.dirX, data->player.dirY);
    return (0);
}

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

void ft_test(t_data *data)
{
	mlx_hook(data->win, 2, 1L << 0, key_pressed, data);	
	mlx_hook(data->win, 3, 1L << 1, key_released, data);
	mlx_loop_hook(data->mlx, multi_key, data);
	mlx_loop(data->mlx);
}


int     game_manager(t_data *data)
{
	data->win_height = 500;
	data->win_width = 500;
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, data->win_width, data->win_height, "Backroom cub3d"); 
	generate_base_img(data);
	get_image(data);
	create_image(data);

	printf("%d\n",tab_size(data->map_info.map));
	data->last_frame = get_current_time();

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

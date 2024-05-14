/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leoherna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:25:26 by leoherna          #+#    #+#             */
/*   Updated: 2024/04/24 14:25:26 by leoherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void draw_scaled_vector(void *mlx_ptr, void *win_ptr, double x_origin, double y_origin, double x_vector, double y_vector);

void	send_rays(t_data *data)
{
	int		x;
	double	raydirx;
	double	raydiry;
	double	camx;

	x = 0;
	//printf("{%f, %f}\n", data->player.posX, data->player.posY);
	while (x < data->win_width)
	{
		camx = 2 * x / (double)(data->win_width) - 1;
		raydirx = data->player.dirX + data->player.planX * camx;
		raydiry = data->player.dirY + data->player.planY * camx;
		one_ray(data, raydirx, raydiry);
		x++;
		draw_scaled_vector(data->mlx, data->win, data->player.posX * 50, data->player.posY * 50, raydirx, raydiry);
		//printf("{%f, %f}\n", raydirx, raydiry);
	}
}

void	one_ray(t_data *data, double rdX, double rdY)
{
	t_raystate	raystate;

	raystate.hit = 0;
	raystate.mapX = (int)(data->player.posX);
	raystate.mapY = (int)(data->player.posY);
	if (rdX == 0)
		raystate.deltaDistX = 1e30;
	else
		raystate.deltaDistX = fabs((double)(1 / rdX));
	if (rdY == 0)
		raystate.deltaDistY = 1e30;
	else
		raystate.deltaDistY = fabs((double)(1 / rdY));
	calculate_init_dist(data, &raystate, rdX, rdY);
	ray_loop(data, &raystate);
}

void	calculate_init_dist(t_data *data, t_raystate *raystate, int rdx, int rdy)
{
	if (rdx < 0)
	{
		raystate->stepX = -1;
		raystate->sideDistX = (data->player.posX - raystate->mapX) * raystate->deltaDistX;
	}
	else
	{
		raystate->stepX = 1;
		raystate->sideDistX = (raystate->mapX + 1.0 - data->player.posX) * raystate->deltaDistX;
	}
	if (rdy < 0)
	{
		raystate->stepY = -1;
		raystate->sideDistY = (data->player.posY - raystate->mapY) * raystate->deltaDistY;
	}
	else
	{
		raystate->stepY = 1;
		raystate->sideDistY = (raystate->mapY + 1.0 - data->player.posY) * raystate->deltaDistY;
	}
}

void	ray_loop(t_data *data, t_raystate *raystate)
{
	while (raystate->hit == 0)
	{
		//jump to next map square, either in x-direction, or in y-direction
		if (raystate->sideDistX < raystate->sideDistY)
		{
			raystate->sideDistX += raystate->deltaDistX;
			raystate->mapX += raystate->stepX;
			raystate->side = 0;
		}
		else
		{
			raystate->sideDistY += raystate->deltaDistY;
			raystate->mapY += raystate->stepY;
			raystate->side = 1;
		}
		//Check if ray has hit a wall
		if (data->map_info.map[raystate->mapY][raystate->mapX] == '1')
			raystate->hit = 1;
	}
	//printf("vectors -> {%f, %f}\n", raystate->sideDistX , raystate->sideDistY);
	draw_scaled_vector(data->mlx, data->win, data->player.posX * 50, data->player.posY * 50, raystate->sideDistX / raystate->deltaDistX, raystate->sideDistY / raystate->deltaDistY);
}

void draw_scaled_vector(void *mlx_ptr, void *win_ptr, double x_origin, double y_origin, double x_vector, double y_vector)
{
    double x = x_origin;
    double y = y_origin;
    double scaled_x = x_origin + x_vector * 50;
    double scaled_y = y_origin + y_vector * 50;

    double dx = scaled_x - x_origin;
    double dy = scaled_y - y_origin;
    double step = fmax(fabs(dx), fabs(dy)); // Determine la plus grande valeur absolue entre dx et dy
    double x_increment = dx / step;
    double y_increment = dy / step;

    for (int i = 0; i < step; i++)
    {
        mlx_pixel_put(mlx_ptr, win_ptr, round(x), round(y), 0xFF0000); // Dessine un pixel rouge à la position actuelle
        x += x_increment;
        y += y_increment;
    }
}
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

void	send_rays(t_data *data)
{
	int		x;
	double	camx;
	double	raydirx;
	double	raydiry;

	x = 0;
	if (data->texture.ceiling_color_or_texture == 1
		&& data->player.drug_level < 5)
		cast_floor(data);
	while (x < data->win_width)
	{
		camx = ((2 * x) / (double)(data->win_width)) - 1;
		raydirx = data->player.dirX + (data->player.planX * camx);
		raydiry = data->player.dirY + (data->player.planY * camx);
		one_ray(data, raydirx, raydiry, x);
		x++;
	}
	give_effect(data);
	cast_sprite(data);
	print_map(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img_ptr, 0, 0);
}

void	one_ray(t_data *data, double rdX, double rdY, int x)
{
	t_raystate	raystate;

	raystate.x = x;
	raystate.hit = 0;
	raystate.mapX = (int)(data->player.posX);
	raystate.mapY = (int)(data->player.posY);
	raystate.rayDirX = rdX;
	raystate.rayDirY = rdY;
	if (rdX == 0)
		raystate.deltaDistX = 1e30;
	else
		raystate.deltaDistX = fabs(1 / rdX);
	if (rdY == 0)
		raystate.deltaDistY = 1e30;
	else
		raystate.deltaDistY = fabs(1 / rdY);
	calculate_init_dist(data, &raystate, rdX, rdY);
	ray_loop(data, &raystate);
}

void	calculate_init_dist(t_data *data,
		t_raystate *raystate, double rdx, double rdy)
{
	if (rdx < 0)
	{
		raystate->stepX = -1;
		raystate->sideDistX = (data->player.posX - raystate->mapX)
			* raystate->deltaDistX;
	}
	else
	{
		raystate->stepX = 1;
		raystate->sideDistX = (raystate->mapX + 1.0 - data->player.posX)
			* raystate->deltaDistX;
	}
	if (rdy < 0)
	{
		raystate->stepY = -1;
		raystate->sideDistY = (data->player.posY - raystate->mapY)
			* raystate->deltaDistY;
	}
	else
	{
		raystate->stepY = 1;
		raystate->sideDistY = (raystate->mapY + 1.0 - data->player.posY)
			* raystate->deltaDistY;
	}
}

void	ray_loop(t_data *data, t_raystate *raystate)
{
	while (raystate->hit == 0)
	{
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
		if (data->map_info.map[raystate->mapY][raystate->mapX] == '1')
			raystate->hit = 1;
	}
	if (raystate->side == 0)
		raystate->perpWallDist = (raystate->sideDistX - raystate->deltaDistX);
	else
		raystate->perpWallDist = (raystate->sideDistY - raystate->deltaDistY);
	get_line_data(data, raystate);
}

void	which_texture(t_data *data, t_raystate *raystate,
	int l_start, int l_end)
{
	t_var	var;

	var.lend = l_end;
	var.lstart = l_start;
	if (raystate->side == 0 && raystate->mapX > data->player.posX)
		drawverticalline(data, raystate, &(data->texture.Ewall), &var);
	if (raystate->side == 0 && raystate->mapX < data->player.posX)
		drawverticalline(data, raystate, &(data->texture.Wwall), &var);
	if (raystate->side == 1 && raystate->mapY > data->player.posY)
		drawverticalline(data, raystate, &(data->texture.Swall), &var);
	if (raystate->side == 1 && raystate->mapY < data->player.posY)
		drawverticalline(data, raystate, &(data->texture.Nwall), &var);
}

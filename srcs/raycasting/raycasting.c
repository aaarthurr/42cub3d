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
		raydirx = data->player.dirx + (data->player.planx * camx);
		raydiry = data->player.diry + (data->player.plany * camx);
		one_ray(data, raydirx, raydiry, x);
		x++;
	}
	give_effect(data);
	cast_sprite(data);
	print_map(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img_ptr, 0, 0);
}

void	one_ray(t_data *data, double rdx, double rdy, int x)
{
	t_raystate	raystate;

	raystate.x = x;
	raystate.hit = 0;
	raystate.mapx = (int)(data->player.posx);
	raystate.mapy = (int)(data->player.posy);
	raystate.raydirx = rdx;
	raystate.raydiry = rdy;
	if (rdx == 0)
		raystate.deltadistx = 1e30;
	else
		raystate.deltadistx = fabs(1 / rdx);
	if (rdy == 0)
		raystate.deltadisty = 1e30;
	else
		raystate.deltadisty = fabs(1 / rdy);
	calculate_init_dist(data, &raystate, rdx, rdy);
	ray_loop(data, &raystate);
}

void	calculate_init_dist(t_data *data,
		t_raystate *raystate, double rdx, double rdy)
{
	if (rdx < 0)
	{
		raystate->stepx = -1;
		raystate->sidedistx = (data->player.posx - raystate->mapx)
			* raystate->deltadistx;
	}
	else
	{
		raystate->stepx = 1;
		raystate->sidedistx = (raystate->mapx + 1.0 - data->player.posx)
			* raystate->deltadistx;
	}
	if (rdy < 0)
	{
		raystate->stepy = -1;
		raystate->sidedisty = (data->player.posy - raystate->mapy)
			* raystate->deltadisty;
	}
	else
	{
		raystate->stepy = 1;
		raystate->sidedisty = (raystate->mapy + 1.0 - data->player.posy)
			* raystate->deltadisty;
	}
}

void	ray_loop(t_data *data, t_raystate *raystate)
{
	while (raystate->hit == 0)
	{
		if (raystate->sidedistx < raystate->sidedisty)
		{
			raystate->sidedistx += raystate->deltadistx;
			raystate->mapx += raystate->stepx;
			raystate->side = 0;
		}
		else
		{
			raystate->sidedisty += raystate->deltadisty;
			raystate->mapy += raystate->stepy;
			raystate->side = 1;
		}
		if (data->map_info.map[raystate->mapy][raystate->mapx] == '1')
			raystate->hit = 1;
	}
	if (raystate->side == 0)
		raystate->perpwalldist = (raystate->sidedistx - raystate->deltadistx);
	else
		raystate->perpwalldist = (raystate->sidedisty - raystate->deltadisty);
	get_line_data(data, raystate);
}

void	which_texture(t_data *data, t_raystate *raystate,
	int l_start, int l_end)
{
	t_var	var;

	var.lend = l_end;
	var.lstart = l_start;
	if (raystate->side == 0 && raystate->mapx > data->player.posx)
		drawverticalline(data, raystate, &(data->texture.ewall), &var);
	if (raystate->side == 0 && raystate->mapx < data->player.posx)
		drawverticalline(data, raystate, &(data->texture.wwall), &var);
	if (raystate->side == 1 && raystate->mapy > data->player.posy)
		drawverticalline(data, raystate, &(data->texture.swall), &var);
	if (raystate->side == 1 && raystate->mapy < data->player.posy)
		drawverticalline(data, raystate, &(data->texture.nwall), &var);
}

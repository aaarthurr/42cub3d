/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   roof_cast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leoherna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 13:49:42 by leoherna          #+#    #+#             */
/*   Updated: 2024/09/28 15:04:15 by leoherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	cast_floor_ter(t_data *data, t_roofstate *rstate)
{
	int	cell_x;
	int	cell_y;
	int	tx;
	int	ty;
	int	color;

	cell_x = (int)(rstate->floorx);
	cell_y = (int)(rstate->floory);
	tx = (int)(TEX_SIZE * (rstate->floorx - cell_x)) & (TEX_SIZE - 1);
	ty = (int)(TEX_SIZE * (rstate->floory - cell_y)) & (TEX_SIZE - 1);
	rstate->floorx += rstate->floorstepx;
	rstate->floory += rstate->floorstepy;
	color = get_pixel_color(&(data->texture.ceiling), tx, ty);
	pixel_put_opti(&(data->img), rstate->x,
		(data->win_height - rstate->y - 1), color);
}

void	cast_floor_bis(t_data *data, t_roofstate rstate, int y)
{
	int		x;
	float	pos_z;
	float	row_distance;

	rstate.y = y;
	x = 0;
	rstate.p = (int)(y - (data->win_height / 2));
	pos_z = data->player.posz * data->win_height;
	row_distance = pos_z / rstate.p;
	rstate.floorstepx = row_distance
		* (rstate.raydirx1 - rstate.raydirx0) / data->win_width;
	rstate.floorstepy = row_distance
		* (rstate.raydiry1 - rstate.raydiry0) / data->win_width;
	rstate.floorx = ((data->player.posx) + (row_distance * rstate.raydirx0));
	rstate.floory = ((data->player.posy) + (row_distance * rstate.raydiry0));
	while (x < data->win_width)
	{
		rstate.x = x;
		cast_floor_ter(data, &rstate);
		x++;
	}
}

void	cast_floor(t_data *data)
{
	t_roofstate	roofstate;
	int			y;

	y = data->win_height / 2;
	roofstate.raydirx0 = data->player.dirx - data->player.planx;
	roofstate.raydiry0 = data->player.diry - data->player.plany;
	roofstate.raydirx1 = data->player.dirx + data->player.planx;
	roofstate.raydiry1 = data->player.diry + data->player.plany;
	while (y < data->win_height)
	{
		cast_floor_bis(data, roofstate, y);
		y++;
	}
}

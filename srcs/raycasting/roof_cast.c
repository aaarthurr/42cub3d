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

	cell_x = (int)(rstate->floorX);
	cell_y = (int)(rstate->floorY);
	tx = (int)(TEX_SIZE * (rstate->floorX - cell_x)) & (TEX_SIZE - 1);
	ty = (int)(TEX_SIZE * (rstate->floorY - cell_y)) & (TEX_SIZE - 1);
	rstate->floorX += rstate->floorStepX;
	rstate->floorY += rstate->floorStepY;
	color = get_pixel_color(&(data->texture.ceiling), tx, ty);
	pixel_put_opti(&(data->img), rstate->x, (data->win_height - rstate->y - 1), color);
}

void	cast_floor_bis(t_data *data, t_roofstate rstate, int y)
{
	int		x;
	float	pos_z;
	float	row_distance;

	rstate.y = y;
	x = 0;
	rstate.p = (int)(y - (data->win_height / 2));
	pos_z = data->player.posZ * data->win_height;
	row_distance = pos_z / rstate.p;
	rstate.floorStepX = row_distance * (rstate.rayDirX1 - rstate.rayDirX0) / data->win_width;
	rstate.floorStepY = row_distance * (rstate.rayDirY1 - rstate.rayDirY0) / data->win_width;
	rstate.floorX = ((data->player.posX) + (row_distance * rstate.rayDirX0));
	rstate.floorY = ((data->player.posY) + (row_distance * rstate.rayDirY0));
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
	roofstate.rayDirX0 = data->player.dirX - data->player.planX;
	roofstate.rayDirY0 = data->player.dirY - data->player.planY;
	roofstate.rayDirX1 = data->player.dirX + data->player.planX;
	roofstate.rayDirY1 = data->player.dirY + data->player.planY;
	while (y < data->win_height)
	{
		cast_floor_bis(data, roofstate, y);
		y++;
	}
}

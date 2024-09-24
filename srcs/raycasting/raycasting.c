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
	cast_floor(data);
	//printf("{%f, %f}\n", data->player.posX, data->player.posY);
	while (x < data->win_width)
	{
		camx = ((2 * x) / (double)(data->win_width)) - 1;
		raydirx = data->player.dirX + (data->player.planX * camx);
		raydiry = data->player.dirY + (data->player.planY * camx);
		one_ray(data, raydirx, raydiry, x);
		x++;
		//printf("{%f, %f}\n", raydirx, raydiry);
	}
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

void	calculate_init_dist(t_data *data, t_raystate *raystate, double rdx, double rdy)
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
	if (raystate->side == 0)
		raystate->perpWallDist = (raystate->sideDistX - raystate->deltaDistX);
	else
		raystate->perpWallDist = (raystate->sideDistY - raystate->deltaDistY);
	get_line_data(data, raystate);
}

void which_texture(t_data *data, t_raystate *raystate, 	int l_start, int l_end)
{
	if (raystate->side == 0 && raystate->mapX > data->player.posX)
		drawVerticalLine(data, raystate, l_start, l_end, &(data->texture.Ewall));
	if (raystate->side == 0 && raystate->mapX < data->player.posX)
		drawVerticalLine(data, raystate, l_start, l_end, &(data->texture.Wwall));
	if (raystate->side == 1 && raystate->mapY > data->player.posY)
		drawVerticalLine(data, raystate, l_start, l_end, &(data->texture.Swall));
	if (raystate->side == 1 && raystate->mapY < data->player.posY)
		drawVerticalLine(data, raystate, l_start, l_end, &(data->texture.Nwall));
	//drawVerticalLine(data, raystate, l_start, l_end, &(data->texture.wall));
}

void get_line_data(t_data *data, t_raystate *raystate)
{
	int line_height;
	int l_start;
	int l_end;

	line_height = (int)(data->win_height / raystate->perpWallDist);
	raystate->line_height = line_height;
	l_start = (-line_height / 2 + data->win_height / 2);
	l_end = (line_height / 2 + data->win_height / 2);
	raystate->calculated_len = l_end - l_start;
	reajust_line(data, raystate, &l_start, &l_end);
	//part2
	if (raystate->side == 0)
		raystate->wallX = data->player.posY + (raystate->perpWallDist * raystate->rayDirY);
	else
		raystate->wallX = data->player.posX + (raystate->perpWallDist * raystate->rayDirX);
	raystate->wallX -= floor(raystate->wallX);
	//printf("wall it at %f coordinate", raystate->wallX);
	raystate->texX = (int)(raystate->wallX * (double)(TEX_SIZE));
	if (raystate->side == 0 && raystate->rayDirX > 0)
		raystate->texX = TEX_SIZE - raystate->texX - 1;
	if (raystate->side == 1 && raystate->rayDirY < 0)
		raystate->texX = TEX_SIZE - raystate->texX - 1;
	//printf("%d\n", raystate->side);
	//drawVerticalLine(data, raystate, l_start, l_end, &(data->texture.wall));
	which_texture(data, raystate, l_start, l_end);
}

void	reajust_line(t_data *data, t_raystate *raystate, int *l_start, int *l_end)
{
	int len;
	int mid_pix;

	len = *l_end - *l_start;
	mid_pix = round(len * data->player.posZ);
	raystate->offset = (len / 2) - mid_pix;
	*l_start += raystate->offset;
	*l_end = *l_start + raystate->calculated_len;
	if (*l_start < 0)
		*l_start = 0;
	if (*l_end < 0)
		*l_end = 0;
	if (*l_start >= data->win_height)
		*l_start = data->win_height - 1;
	if (*l_end >= data->win_height)
		*l_end = data->win_height- 1;
}

int assombrirCouleur(int couleurOriginale, int assombrissement)
{
	if (assombrissement < 1)
		return(couleurOriginale);
    // Extraire les composantes RVB de la couleur originale
    int rouge = (couleurOriginale >> 16) & 0xFF;
    int vert = (couleurOriginale >> 8) & 0xFF;
    int bleu = couleurOriginale & 0xFF;

    // Assombrir chaque composante RVB en soustrayant l'assombrissement
    rouge -= assombrissement ;
    vert -= assombrissement ;
    bleu -= assombrissement ;

	//* (int)(257 / (bleu + 1)))

    // S'assurer que les valeurs RVB restent dans la plage valide (0-255)
    if (rouge < 0) rouge = 0;
    if (vert < 0) vert = 0;
    if (bleu < 0) bleu = 0;

    // Reconstruire la nouvelle valeur de couleur
    int nouvelleCouleur = (rouge << 16) | (vert << 8) | bleu;
    
    return nouvelleCouleur;
}
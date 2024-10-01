/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_bis.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leoherna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:25:26 by leoherna          #+#    #+#             */
/*   Updated: 2024/04/24 14:25:26 by leoherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	get_line_data(t_data *data, t_raystate *raystate)
{
	int	line_height;
	int	l_start;
	int	l_end;

	line_height = (int)(data->win_height / raystate->perpWallDist);
	raystate->line_height = line_height;
	l_start = (-line_height / 2 + data->win_height / 2);
	l_end = (line_height / 2 + data->win_height / 2);
	raystate->calculated_len = l_end - l_start;
	reajust_line(data, raystate, &l_start, &l_end);
	if (raystate->side == 0)
		raystate->wallX = data->player.posY
			+ (raystate->perpWallDist * raystate->rayDirY);
	else
		raystate->wallX = data->player.posX
			+ (raystate->perpWallDist * raystate->rayDirX);
	raystate->wallX -= floor(raystate->wallX);
	raystate->texX = (int)(raystate->wallX * (double)(TEX_SIZE));
	if (raystate->side == 0 && raystate->rayDirX > 0)
		raystate->texX = TEX_SIZE - raystate->texX - 1;
	if (raystate->side == 1 && raystate->rayDirY < 0)
		raystate->texX = TEX_SIZE - raystate->texX - 1;
	which_texture(data, raystate, l_start, l_end);
}

void	reajust_line(t_data *data,
	t_raystate *raystate, int *l_start, int *l_end)
{
	int	len;
	int	mid_pix;

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
		*l_end = data->win_height - 1;
}

int	assombrircouleur(int couleuroriginale, int assombrissement)
{
	int	nouvellecouleur;
	int	rouge;
	int	vert;
	int	bleu;

	if (assombrissement < 1)
		return (couleuroriginale);
	rouge = (couleuroriginale >> 16) & 0xFF;
	vert = (couleuroriginale >> 8) & 0xFF;
	bleu = couleuroriginale & 0xFF;
	rouge -= assombrissement ;
	vert -= assombrissement ;
	bleu -= assombrissement ;
	if (rouge < 0)
		rouge = 0;
	if (vert < 0)
		vert = 0;
	if (bleu < 0)
		bleu = 0;
	nouvellecouleur = (rouge << 16) | (vert << 8) | bleu;
	return (nouvellecouleur);
}

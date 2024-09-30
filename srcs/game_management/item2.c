/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   item2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leoherna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 10:59:08 by leoherna          #+#    #+#             */
/*   Updated: 2024/09/30 10:59:08 by leoherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	reajust_line_pills(t_data *data, t_spritestate *sp, int *l_start, int *l_end)
{
	int len;
	int mid_pix;

	len = *l_end - *l_start;
	mid_pix = round(len * data->player.posZ);
	sp->offset = (len / 2) - mid_pix;
	*l_start += sp->offset;
	*l_end = *l_start + sp->calculated_len;
	if (*l_start < 0)
		*l_start = 0;
	if (*l_end < 0)
		*l_end = 0;
	if (*l_start >= data->win_height)
		*l_start = data->win_height - 1;
	if (*l_end >= data->win_height)
		*l_end = data->win_height- 1;
}

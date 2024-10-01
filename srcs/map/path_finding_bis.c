/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finding_bis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leoherna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 14:01:57 by leoherna          #+#    #+#             */
/*   Updated: 2024/09/23 14:01:57 by leoherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cubed.h"

int	try_up_down(t_data *data, t_actpos act, t_pos *pos, t_var *var)
{
	if (var->tab[act.act_y + 1][act.act_x] != '1'
		&& var->tab[act.act_y + 1][act.act_x] != '2')
	{
		pos[var->top].y = act.act_y + 1;
		pos[var->top].x = act.act_x;
		if (should_i_be_here(1, act, var->tab, data) == 1)
			return (1);
		var->tab[act.act_y + 1][act.act_x] = '2';
		var->top++;
	}
	if (var->tab[act.act_y - 1][act.act_x] != '1'
		&& var->tab[act.act_y - 1][act.act_x] != '2')
	{
		pos[var->top].y = act.act_y - 1;
		pos[var->top].x = act.act_x;
		if (should_i_be_here(2, act, var->tab, data) == 1)
			return (1);
		var->tab[act.act_y - 1][act.act_x] = '2';
		var->top++;
	}
	return (0);
}

int	try_left_right(t_data *data, t_actpos act, t_pos *pos, t_var *var)
{
	if (var->tab[act.act_y][act.act_x + 1] != '1'
		&& var->tab[act.act_y][act.act_x + 1] != '2')
	{
		pos[var->top].y = act.act_y;
		pos[var->top].x = act.act_x + 1;
		if (should_i_be_here(3, act, var->tab, data) == 1)
			return (1);
		var->tab[act.act_y][act.act_x + 1] = '2';
		var->top++;
	}
	if (var->tab[act.act_y][act.act_x - 1] != '1'
		&& var->tab[act.act_y][act.act_x - 1] != '2')
	{
		pos[var->top].y = act.act_y;
		pos[var->top].x = act.act_x - 1;
		if (should_i_be_here(4, act, var->tab, data) == 1)
			return (1);
		var->tab[act.act_y][act.act_x - 1] = '2';
		var->top++;
	}
	return (0);
}

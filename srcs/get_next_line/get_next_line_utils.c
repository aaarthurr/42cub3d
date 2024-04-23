/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leoherna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 18:35:48 by arpages           #+#    #+#             */
/*   Updated: 2024/04/23 12:31:45 by leoherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

int	found_newline(t_list *temp)
{
	int		i;
	t_list	*current;

	if (temp == NULL)
		return (0);
	current = ft_lst_get_last(temp);
	i = 0;
	while (current->ctnt[i])
	{
		if (current->ctnt[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

t_list	*ft_lst_get_last(t_list *temp)
{
	t_list	*current;

	current = temp;
	while (current && current->next)
		current = current->next;
	return (current);
}

void	generate_line(char **line, t_list *temp)
{
	int	i;
	int	len;

	len = 0;
	while (temp)
	{
		i = 0;
		while (temp->ctnt[i])
		{
			if (temp->ctnt[i] == '\n')
			{
				len++;
				break ;
			}
			len++;
			i++;
		}
		temp = temp->next;
	}
	*line = malloc(sizeof(char) * (len + 1));
}

void	free_temp(t_list *temp)
{
	t_list	*current;
	t_list	*next;

	current = temp;
	while (current)
	{
		free(current->ctnt);
		next = current->next;
		free(current);
		current = next;
	}
}

int	ft_len(const char *str)
{
	int	len;

	len = 0;
	while (*(str++))
		len++;
	return (len);
}

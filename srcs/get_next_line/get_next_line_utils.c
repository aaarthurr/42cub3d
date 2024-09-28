/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 13:27:12 by leoherna          #+#    #+#             */
/*   Updated: 2024/09/28 21:28:42 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	found_newline(t_list *stock)
{
	t_list	*current;
	int		i;

	if (stock == NULL)
		return (0);
	current = lst_get_last(stock);
	i = 0;
	while (current -> content[i])
	{
		if (current -> content[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

t_list	*lst_get_last(t_list *stock)
{
	t_list	*last;

	last = stock;
	while (last && last -> next)
		last = last -> next;
	return (last);
}

void	generate_line(char **line, t_list *stock)
{
	int	i;
	int	len;

	len = 0;
	while (stock)
	{
		i = 0;
		while (stock -> content[i])
		{
			if (stock -> content[i] == '\n')
			{
				len++;
				break ;
			}
			len++;
			i++;
		}
		stock = stock -> next;
	}
	*line = malloc(sizeof(char) * (len + 1));
}

void	free_stock(t_list *stock)
{
	t_list	*current;
	t_list	*next;

	current = stock;
	while (current)
	{
		free(current -> content);
		next = current -> next;
		free(current);
		current = next;
	}
}

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i])
	{
		i++;
	}
	return (i);
}

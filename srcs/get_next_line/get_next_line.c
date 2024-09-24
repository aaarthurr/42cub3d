/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leoherna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 13:26:58 by leoherna          #+#    #+#             */
/*   Updated: 2024/02/14 11:53:50 by leoherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_list	*stock = NULL;
	char			*line;
	int				readen;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &line, 0) < 0)
		return (free_stock(stock), stock = NULL, NULL);
	readen = 1;
	line = NULL;
	read_nstock(fd, &stock, &readen);
	if (stock == NULL)
		return (NULL);
	extract_line(stock, &line);
	clean_stock(&stock);
	if (line[0] == '\0')
	{
		free_stock(stock);
		stock = NULL;
		free(line);
		return (NULL);
	}
	return (line);
}

void	read_nstock(int fd, t_list **stock, int *readen)
{
	char	*buf;

	while ((!found_newline(*stock)) && *readen != 0)
	{
		buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (buf == NULL)
			return ;
		*readen = (int)read(fd, buf, BUFFER_SIZE);
		if ((*stock == NULL && *readen == 0) || *readen == -1)
		{
			free(buf);
			return ;
		}
		buf[*readen] = '\0';
		add_to_stock(stock, buf, *readen);
		free(buf);
	}
}

void	add_to_stock(t_list **stock, char *buf, int readen)
{
	t_list	*current;
	t_list	*new_node;
	int		i;

	new_node = malloc(sizeof(t_list));
	if (new_node == NULL)
		return ;
	new_node -> next = NULL;
	new_node -> content = malloc(sizeof(char) * (readen + 1));
	if (new_node -> content == NULL)
		return ;
	i = 0;
	while (buf[i] && i < readen)
	{
		new_node -> content[i] = buf[i];
		i++;
	}
	new_node -> content[i] = '\0';
	if (*stock == NULL)
	{
		*stock = new_node;
		return ;
	}
	current = lst_get_last(*stock);
	current -> next = new_node;
}

void	extract_line(t_list *stock, char **line)
{
	int	i;
	int	len;

	len = 0;
	if (stock == NULL)
		return ;
	generate_line(line, stock);
	if (line == NULL)
		return ;
	while (stock)
	{
		i = 0;
		while (stock -> content[i])
		{
			if (stock -> content[i] == '\n')
			{
				(*line)[len++] = stock -> content[i];
				break ;
			}
			(*line)[len++] = stock -> content[i++];
		}
		stock = stock -> next;
	}
	(*line)[len] = '\0';
}

void	clean_stock(t_list **stock)
{
	t_list	*clean_node;
	t_list	*last;
	int		i;
	int		j;

	j = 0;
	i = 0;
	clean_node = malloc(sizeof(t_list));
	if (clean_node == NULL || stock == NULL)
		return ;
	clean_node -> next = NULL;
	last = lst_get_last(*stock);
	while (last -> content[i] && last -> content[i] != '\n')
		i++;
	if (last -> content[i] == '\n')
		i++;
	clean_node -> content = malloc(sizeof(char)
			* (ft_strlen(last -> content) - i) + 1);
	if (clean_node == NULL)
		return ;
	while (last -> content[i])
		clean_node -> content[j++] = last -> content[i++];
	free_stock(*stock);
	clean_node -> content[j] = '\0';
	*stock = clean_node;
}
/*
int	main()
{
	int		fd;
	char	*line;

	fd = open("test.txt", O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		printf("%s", line);
		if (line == NULL)
			break ;
		free(line);
	}
	return (0);
}*/
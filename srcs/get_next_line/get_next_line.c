/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leoherna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 18:35:57 by arpages           #+#    #+#             */
/*   Updated: 2024/04/23 12:31:50 by leoherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cubed.h"

void	clean_lst(t_list **lst)
{
	t_list	*last;
	t_list	*clean;
	int		i;
	int		j;

	i = 0;
	j = 0;
	clean = malloc(sizeof(t_list));
	if (!clean || !lst)
		return ;
	clean->next = NULL;
	last = ft_lst_get_last(*lst);
	while (last->ctnt[i] && last->ctnt[i] != '\n')
		i++;
	if (last->ctnt[i] && last->ctnt[i] == '\n')
		i++;
	clean->ctnt = malloc(sizeof(char) * ((ft_len(last->ctnt) - i) + 1));
	if (!(clean->ctnt))
		return ;
	while (last->ctnt[i])
		clean->ctnt[j++] = last->ctnt[i++];
	clean->ctnt[j] = '\0';
	free_temp(*lst);
	*lst = clean;
}

void	extract(t_list *lst, char **line)
{
	int	i;
	int	j;

	if (!lst)
		return ;
	generate_line(line, lst);
	if (!(*line))
		return ;
	j = 0;
	while (lst)
	{
		i = 0;
		while (lst->ctnt[i])
		{
			if (lst->ctnt[i] == '\n')
			{
				(*line)[j++] = lst->ctnt[i];
				break ;
			}
			(*line)[j++] = lst->ctnt[i++];
		}
		lst = lst->next;
	}
	(*line)[j] = '\0';
}

void	add_to_lst(t_list **lst, char *buf, int size)
{
	int		i;
	t_list	*last;
	t_list	*new_node;

	i = 0;
	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return ;
	new_node->next = NULL;
	new_node->ctnt = malloc(sizeof(char) * (size + 1));
	if (!(new_node->ctnt))
		return ;
	while (buf[i] && i < size)
	{
		new_node->ctnt[i] = buf[i];
		i++;
	}
	new_node->ctnt[i] = '\0';
	if (!(*lst))
	{
		*lst = new_node;
		return ;
	}
	last = ft_lst_get_last(*lst);
	last->next = new_node;
}

void	read_line(int fd, t_list **lst)
{
	char	*buf;
	int		size;

	size = 1;
	while (!found_newline(*lst) && size != 0)
	{
		buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buf)
			return ;
		size = (int)read(fd, buf, BUFFER_SIZE);
		if ((size < 0 || (size == 0 && *lst == NULL)))
		{
			free(buf);
			return ;
		}
		buf[size] = '\0';
		add_to_lst(lst, buf, size);
		free(buf);
	}
}

char	*get_next_line(int fd)
{
	static t_list	*lst = NULL;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &line, 0) < 0)
	{
		free_temp(lst);
		lst = NULL;
		return (NULL);
	}
	line = NULL;
	read_line(fd, &lst);
	if (!lst)
		return (NULL);
	extract(lst, &line);
	clean_lst(&lst);
	if (line[0] == '\0')
	{
		free_temp(lst);
		lst = NULL;
		free(line);
		return (NULL);
	}
	return (line);
}
/*
int main()
{
	int j;

	j = open("test.txt", O_RDWR);
	printf("next line is --->\n");
	printf("%s\n", get_next_line(j));
	printf("next line is --->\n");
	printf("%s\n", get_next_line(j));
	printf("next line is --->\n");
	printf("%s\n", get_next_line(j));
}
*/
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leoherna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 13:27:03 by leoherna          #+#    #+#             */
/*   Updated: 2023/11/06 13:27:04 by leoherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}			t_list;

int		found_newline(t_list *stock);
int		ft_strlen(const char *str);

char	*get_next_line(int fd);

void	read_nstock(int fd, t_list **stock, int *readen);
void	add_to_stock(t_list **stock, char *buf, int readed);
void	extract_line(t_list *stock, char **line);
void	generate_line(char **line, t_list *stock);
void	clean_stock(t_list **stock);
void	free_stock(t_list *stock);

t_list	*lst_get_last(t_list *stock);
#endif
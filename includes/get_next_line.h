/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arpages <arpages@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 10:59:02 by arpages           #+#    #+#             */
/*   Updated: 2023/10/29 17:51:10 by arpages          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 512
# endif

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>

typedef struct s_list
{
	char			*ctnt;
	struct s_list	*next;
}					t_list;

char	*get_next_line(int fd);

t_list	*ft_lst_get_last(t_list *temp);

void	generate_line(char **line, t_list *temp);
void	free_temp(t_list *temp);
void	clean_lst(t_list **temp);
void	extract(t_list *temp, char **line);
void	add_to_lst(t_list **temp, char *buf, int read_line);
void	read_lst(int fd, t_list **temp);

int		found_newline(t_list *temp);
int		ft_len(const char *str);

#endif
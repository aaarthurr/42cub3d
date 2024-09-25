/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leoherna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:09:32 by arpages           #+#    #+#             */
/*   Updated: 2024/09/25 09:32:19 by leoherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

/* classic realloc funtion*/
char **tab_realloc(char **tab, int m_size, char *content)
{
	int i;
	char **new_tab;

	i = 0;
	if (!tab)
		printf("we are here %d %d\n", m_size, tab_size(tab));
	//print_tab(tab);
	new_tab = malloc(sizeof(char *) * (tab_size(tab) + m_size + 1));
	while (tab != NULL && tab[i] != NULL)
	{
		new_tab[i] = tab[i];
		i++;
	}
	while(i < (tab_size(tab) + m_size))
	{
		new_tab[i] = content;
		i++;
	}
	new_tab[i] = NULL;
	if (tab != NULL)
		free(tab);
	print_tab(new_tab);
	printf("d\n\n");
	
	return(new_tab);
}

/*return size of a tab*/
int tab_size(char **tab)
{
	int i;

	i = 0;
	if(tab == NULL)
		return (0);
	while (tab[i] != NULL)
		i++;
	return (i);
}

void	print_tab(char **tab)
{
	int		i;

	i = 0;
	while (tab[i] != NULL)
	{
        printf("%s", tab[i]);
		i++;
	}
	printf("\n");
}

//return time in milisecond
size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		printf("gettimeofday() error\n");
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}


static int	len(char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strdup(char *src)
{
	int		i;
	int		size;
	char	*copy;

	i = 0;
	size = len(src) + 1;
	copy = malloc (size * sizeof(char));
	if (!copy)
		return (0);
	while (src[i] != '\0')
	{
		copy[i] = src[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}


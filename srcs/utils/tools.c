/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arpages <arpages@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:09:32 by arpages           #+#    #+#             */
/*   Updated: 2024/04/23 16:02:40 by arpages          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

/* classic realloc funtion*/
char **tab_realloc(char **tab, int m_size, char *content)
{
	int i;
	char **new_tab;

	i = 0;
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

int	ft_strlen(char *str)
{
	int i;

	i = 0;
	while(str[i] != '\0')
		i++;
	return(i);
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

int ft_strchr(char c, char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}
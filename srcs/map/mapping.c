
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leoherna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 14:12:26 by arpages           #+#    #+#             */
/*   Updated: 2024/09/25 16:06:21 by leoherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

int check_path_xpm_file(char *str)
{
	int i;

	i = ft_strlen(str);
	while (i > 0)
	{
		i--;
		if (str[i] == '.')
			break ;
	}
	if((str[i + 1] != '\0' && str[i + 1] == 'x')
		&& (str[i + 2] != '\0' && str[i + 2] == 'p')
		&&  (str[i + 3] != '\0' && str[i + 3] == 'm')
		&& str[i + 4] == '\0')
		return (0);
	printf("str[i] -> %c\n", str[i + 4]);
	return (1);
}

int check_path(t_data *data)
{
	int fd;
printf("3here\n");
	fd = open(data->texture.Ewall_path, O_RDONLY);
	if (check_path_xpm_file(data->texture.Ewall_path) == 1 || fd == -1)
		return(printf("Error : Texture Path. ABORTING\n"), 1);
printf("here2\n");
	fd = open(data->texture.Wwall_path, O_RDONLY);
	if (check_path_xpm_file(data->texture.Wwall_path) == 1 || fd == -1)
		return(printf("Error : Texture Path. ABORTING\n"), 1);

printf("1here\n");
	fd = open(data->texture.Nwall_path, O_RDONLY);
	if (check_path_xpm_file(data->texture.Nwall_path) == 1 || fd == -1)
		return(printf("Error : Texture Path. ABORTING\n"), 1);

printf("here\n");
	fd = open(data->texture.Swall_path, O_RDONLY);
	if (check_path_xpm_file(data->texture.Swall_path) == 1 || fd == -1)
		return(printf("Error : Texture Path. ABORTING\n"), 1);
	
	if (data->texture.ceiling_color_or_texture == 1)
	{
		
		fd = open(data->texture.ceiling_path, O_RDONLY);
		if (check_path_xpm_file(data->texture.ceiling_path) == 1 || fd == -1)
			return(printf("Error : Texture Path. ABORTING\n"), 1);

	}


	return(0);
}

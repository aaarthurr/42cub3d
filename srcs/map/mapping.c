/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leoherna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 14:12:26 by arpages           #+#    #+#             */
/*   Updated: 2024/09/28 15:20:58 by leoherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

int	check_path_xpm_file(char *str)
{
	int	i;

	if (str == NULL)
		return (1);
	i = ft_strlen(str);
	while (i > 0)
	{
		i--;
		if (str[i] == '.')
			break ;
	}
	if ((str[i + 1] != '\0' && str[i + 1] == 'x')
		&& (str[i + 2] != '\0' && str[i + 2] == 'p')
		&& (str[i + 3] != '\0' && str[i + 3] == 'm')
		&& str[i + 4] == '\0')
		return (0);
	return (1);
}

int	check_path_tools2(t_data *data)
{
	int	fd;

	if (data->texture.nwall_path != NULL)
	{
		fd = open(data->texture.nwall_path, O_RDONLY);
		if (check_path_xpm_file(data->texture.nwall_path) == 1 || fd == -1)
			return (printf("Error N : Texture Path. ABORTING\n"), 1);
	}
	else
		return (1);
	if (data->texture.swall_path != NULL)
	{
		fd = open(data->texture.swall_path, O_RDONLY);
		if (check_path_xpm_file(data->texture.swall_path) == 1 || fd == -1)
			return (printf("Error S : Texture Path. ABORTING\n"), 1);
	}
	else
		return (1);
	return (0);
}

int	check_path_tools(t_data *data)
{
	int	fd;

	if (data->texture.ewall_path != NULL)
	{
		fd = open(data->texture.ewall_path, O_RDONLY);
		if (check_path_xpm_file(data->texture.ewall_path) == 1 || fd == -1)
			return (printf("Error E : Texture Path. ABORTING\n"), 1);
	}
	else
		return (1);
	if (data->texture.wwall_path != NULL)
	{
		fd = open(data->texture.wwall_path, O_RDONLY);
		if (check_path_xpm_file(data->texture.wwall_path) == 1 || fd == -1)
			return (printf("Error W : Texture Path. ABORTING\n"), 1);
	}
	else
		return (1);
	return (0);
}

int	check_path(t_data *data)
{
	int	fd;

	if (check_path_tools(data) == 1)
		return (1);
	if (check_path_tools2(data) == 1)
		return (1);
	if (data->texture.ceiling_color_or_texture
		== 1 && data->texture.ceiling_path != NULL)
	{
		fd = open(data->texture.ceiling_path, O_RDONLY);
		if (check_path_xpm_file(data->texture.ceiling_path) == 1 || fd == -1)
			return (printf("Error C : Texture Path. ABORTING\n"), 1);
	}
	fd = open("textures/pills.xpm", O_RDONLY);
	if (check_path_xpm_file("textures/pills.xpm") == 1 || fd == -1)
		return (printf("Error sprite : Texture Path. ABORTING\n"), 1);
	return (0);
}

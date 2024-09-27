/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leoherna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 15:21:58 by arthur            #+#    #+#             */
/*   Updated: 2024/09/28 15:33:56 by leoherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"


char *generate_path(t_data *data,int index, char *which_texture)
{
	int i;
	int len;
	int j;
	char *temp;

	i = 2;
	j = 0;
	len = 0;
	temp = NULL;
	if (ft_strncmp(data->map_info.global[index], which_texture, ft_strlen(which_texture)) == 0)
	{
		while (data->map_info.global[index][i] != '\0' && data->map_info.global[index][i] == ' ')
			i++;
		while (data->map_info.global[index][i] != '\n' && data->map_info.global[index][i] != '\0')
		{
			len++;
			i++;
		}
		
		temp = malloc(sizeof(char) * (len + 1));
		i = i - len;
		while (data->map_info.global[index][i] != '\n' && data->map_info.global[index][i] != '\0')//mettre i+1 pour le \n de temps en temps wtf
		{
			temp[j] = data->map_info.global[index][i];
			i++;
			j++;
		}
		temp[j] = '\0';
	}
	return(temp);
}

void	init_image(t_data *data)
{
	int	x;
	int	y;
	int s;

	s = SPRITE_SIZE;
	x = TEX_SIZE;
	y = TEX_SIZE;
	data->texture.Nwall.img_ptr = NULL;
	data->texture.Swall.img_ptr = NULL;
	data->texture.Wwall.img_ptr = NULL;
	data->texture.Ewall.img_ptr = NULL;
	data->texture.ceiling.img_ptr = NULL;
	data->texture.pills.img_ptr = NULL;

	data->texture.Nwall.img_ptr = mlx_xpm_file_to_image(data->mlx, data->texture.Nwall_path, &x, &y);
	data->texture.Swall.img_ptr = mlx_xpm_file_to_image(data->mlx, data->texture.Swall_path, &x, &y);
	data->texture.Wwall.img_ptr = mlx_xpm_file_to_image(data->mlx, data->texture.Wwall_path, &x, &y);
	data->texture.Ewall.img_ptr = mlx_xpm_file_to_image(data->mlx, data->texture.Ewall_path, &x, &y);
	data->texture.pills.img_ptr = mlx_xpm_file_to_image(data->mlx, "textures/pills.xpm", &s, &s);
	if (data->texture.ceiling_color_or_texture == 1)
		data->texture.ceiling.img_ptr = mlx_xpm_file_to_image(data->mlx, data->texture.ceiling_path, &x, &y);
}

char	*find_arg(t_data *data, char *which_texture)
{
	int		i;
	char *path;

	i = 0;
	path = NULL;
	while (i < data->map_info.global_len)//data->map_info.global[i] != NULL || (data->map_info.global[i][0] != '0' || data->map_info.global[i][0] != '1'))
	{
			if (ft_strncmp(data->map_info.global[i], which_texture, ft_strlen(which_texture)) == 0)
			{
				path = generate_path(data, i, which_texture);
				printf("path : %s\n", path);
				return (path);			
			}
			i++;
	}
	return (NULL);
}

void	get_image(t_data *data)
{
	data->texture.ceiling_color_or_texture = 0;
	data->texture.Nwall_path = find_arg(data, "NO");
	data->texture.Swall_path = find_arg(data, "SO");
	data->texture.Wwall_path = find_arg(data, "WE");
	data->texture.Ewall_path = find_arg(data, "EA");
	if(search_floor_color(data) == 1)
		exit_manager(data);
	if (search_ceiling_color(data) == 1)
	{
		data->texture.ceiling_color_or_texture = 1;
		data->texture.ceiling_path = find_arg(data, "C");
	}
	else if (search_ceiling_color(data) == 2)
		exit_manager(data);
	if (check_path(data) == 1)
		exit_manager(data);
	init_image(data);
}

void    create_image(t_data *data)
{
	data->texture.Nwall.img_char = mlx_get_data_addr(data->texture.Nwall.img_ptr,
		&data->texture.Nwall.bits_pix, &data->texture.Nwall.len, &data->texture.Nwall.endian);
	data->texture.Swall.img_char = mlx_get_data_addr(data->texture.Swall.img_ptr,
		&data->texture.Swall.bits_pix, &data->texture.Swall.len, &data->texture.Swall.endian);
	data->texture.Wwall.img_char = mlx_get_data_addr(data->texture.Wwall.img_ptr,
		&data->texture.Wwall.bits_pix, &data->texture.Wwall.len, &data->texture.Wwall.endian);
	data->texture.Ewall.img_char = mlx_get_data_addr(data->texture.Ewall.img_ptr,
		&data->texture.Ewall.bits_pix, &data->texture.Ewall.len, &data->texture.Ewall.endian);
	if (data->texture.ceiling_color_or_texture == 1)
	{
		data->texture.ceiling.img_char = mlx_get_data_addr(data->texture.ceiling.img_ptr,
			&data->texture.ceiling.bits_pix, &data->texture.ceiling.len, &data->texture.ceiling.endian);
	}
	data->texture.pills.img_char = mlx_get_data_addr(data->texture.pills.img_ptr,
		&data->texture.pills.bits_pix, &data->texture.pills.len, &data->texture.pills.endian);
}
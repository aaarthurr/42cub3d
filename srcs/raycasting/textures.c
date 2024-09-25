/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leoherna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 15:21:58 by arthur            #+#    #+#             */
/*   Updated: 2024/09/25 16:49:45 by leoherna         ###   ########.fr       */
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
		while (data->map_info.global[index][i] !='\0')
		{
			len++;
			i++;
		}
		temp = malloc(sizeof(char) * (len));
		i = i - len;
		while (data->map_info.global[index][i] != '\0')
		{
			temp[j] = data->map_info.global[index][i];
			i++;
			j++;
		}
		temp[j - 1] = '\0';
	}
	return(temp);
}

void	init_image(t_data *data)
{
	int	x;
	int	y;

	x = TEX_SIZE;
	y = TEX_SIZE;

	
	
	data->texture.Nwall.img_ptr = NULL;
	data->texture.Swall.img_ptr = NULL;
	data->texture.Wwall.img_ptr = NULL;
	data->texture.Ewall.img_ptr = NULL;
	data->texture.ceiling.img_ptr = NULL;
	
	printf("NO path : |%s|\n", data->texture.Nwall_path);
	printf("SO path : |%s|\n", data->texture.Swall_path);
	printf("WE path : |%s|\n", data->texture.Wwall_path);
	printf("EA path : |%s|\n", data->texture.Ewall_path);
	//printf("C path : |%s|\n", data->texture.ceiling_path);
	
	data->texture.Nwall.img_ptr = mlx_xpm_file_to_image(data->mlx, data->texture.Nwall_path, &x, &y);
	data->texture.Swall.img_ptr = mlx_xpm_file_to_image(data->mlx, data->texture.Swall_path, &x, &y);
	data->texture.Wwall.img_ptr = mlx_xpm_file_to_image(data->mlx, data->texture.Wwall_path, &x, &y);
	data->texture.Ewall.img_ptr = mlx_xpm_file_to_image(data->mlx, data->texture.Ewall_path, &x, &y);
	
	//if (data->texture != "null")
	if (data->texture.ceiling_color_or_texture == 1)
		data->texture.ceiling.img_ptr = mlx_xpm_file_to_image(data->mlx, data->texture.ceiling_path, &x, &y);

	
}


int	find_arg(char c, char f, char **map)
{
	int	i;
	int	j;

	j = -1;
	i = 0;
	while (map[i])
	{
		if (map[i][0] == c && map[i][1] == f)
		{
			if (j != -1)
				return (-1);
			if (f == '\0')
				return (3);
			if (f == ' ')
				j = i + 1;
			if (f != ' ' && ft_lenxd(map[i]) == 3)
				j = i + 1;
		}
		i++;
	}
	return (j - 1);
}

void	get_image(t_data *data)
{
	int trigger;
	
	trigger = 0;
	data->texture.ceiling_color_or_texture = 0;
	

	data->texture.Nwall_path = generate_path(data, 0, "NO");
	data->texture.Swall_path = generate_path(data, 1, "SO");
	data->texture.Wwall_path = generate_path(data, 2, "WE");
	data->texture.Ewall_path = generate_path(data, 3, "EA");
	if(search_floor_color(data) == 1)
		exit(0);
	if (search_ceiling_color(data) == 1)
	{
		data->texture.ceiling_color_or_texture = 1;
		data->texture.ceiling_path = generate_path(data, 5, "C");
		printf("path -> %s\n", data->texture.ceiling_path);
	}

	if (check_path(data) == 1)
		exit(0);


	//data->texture.floor_color = 0x000000;
	//a enlever hein!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	init_image(data);
}

void    create_image(t_data *data)
{

//nwall
    data->texture.Nwall.img_char = mlx_get_data_addr(data->texture.Nwall.img_ptr, &data->texture.Nwall.bits_pix, &data->texture.Nwall.len, &data->texture.Nwall.endian);
    data->texture.Nwall.global_color = blend_color(&data->texture.Nwall);
//swall
    data->texture.Swall.img_char = mlx_get_data_addr(data->texture.Swall.img_ptr, &data->texture.Swall.bits_pix, &data->texture.Swall.len, &data->texture.Swall.endian);
    data->texture.Swall.global_color = blend_color(&data->texture.Swall);
//wwall
    data->texture.Wwall.img_char = mlx_get_data_addr(data->texture.Wwall.img_ptr, &data->texture.Wwall.bits_pix, &data->texture.Wwall.len, &data->texture.Wwall.endian);
    data->texture.Wwall.global_color = blend_color(&data->texture.Wwall);
//ewall
    data->texture.Ewall.img_char = mlx_get_data_addr(data->texture.Ewall.img_ptr, &data->texture.Ewall.bits_pix, &data->texture.Ewall.len, &data->texture.Ewall.endian);
    data->texture.Ewall.global_color = blend_color(&data->texture.Ewall);
	
	if (data->texture.ceiling_color_or_texture == 1)
	{
		data->texture.ceiling.img_char = mlx_get_data_addr(data->texture.ceiling.img_ptr, &data->texture.ceiling.bits_pix, &data->texture.ceiling.len, &data->texture.ceiling.endian);
		data->texture.ceiling.global_color = blend_color(&data->texture.ceiling);
	}
}

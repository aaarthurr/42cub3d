/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leoherna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 15:21:58 by arthur            #+#    #+#             */
/*   Updated: 2024/09/24 19:34:40 by leoherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

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
	
	data->texture.Nwall.img_ptr = mlx_xpm_file_to_image(data->mlx, data->texture.Nwall_path, &x, &y);
	data->texture.Swall.img_ptr = mlx_xpm_file_to_image(data->mlx, data->texture.Swall_path, &x, &y);
	data->texture.Wwall.img_ptr = mlx_xpm_file_to_image(data->mlx, data->texture.Wwall_path, &x, &y);
	data->texture.Ewall.img_ptr = mlx_xpm_file_to_image(data->mlx, data->texture.Ewall_path, &x, &y);
	
	//if (data->texture != "null")
	data->texture.ceiling.img_ptr = mlx_xpm_file_to_image(data->mlx, "textures/ceiling.xpm"/*data->texture.ceilling_path*/, &x, &y);
}


void	get_image(t_data *data)
{
	int i;
	int len;
	int j;
	char *temp;

	i = 2;
	j = 0;
	len = 0;
	temp = NULL;
	if (ft_strncmp(data->map_info.global[0], "NO", 2) == 0)
	{
		while (data->map_info.global[0][i] != '\0' && data->map_info.global[0][i] == ' ')
			i++;
		while (data->map_info.global[0][i] !='\0')
		{
			len++;
			i++;
		}
		printf("\n");
		temp = malloc(sizeof(char) * (len));
		i = i - len;
		while (data->map_info.global[0][i] != '\0')
		{
			temp[j] = data->map_info.global[0][i];
			i++;
			j++;
		}
		temp[j - 1] = '\0';
		data->texture.Nwall_path = ft_strdup(temp);
		free(temp);
	}
	
	if (ft_strncmp(data->map_info.global[1], "SO", 2) == 0)
	{
		i = 2;
		j = 0;
		len = 0;
		temp = NULL;
		while (data->map_info.global[1][i] != '\0' && data->map_info.global[1][i] == ' ')
			i++;
		while (data->map_info.global[1][i] !='\0')
		{
			
			len++;
			i++;
		}
		temp = malloc(sizeof(char) * (len));
		i = i - len;
		while (data->map_info.global[1][i] != '\0')
		{
			temp[j] = data->map_info.global[1][i];
			i++;
			j++;
		}
		temp[j - 1] = '\0';
		data->texture.Swall_path = ft_strdup(temp);
		free(temp);
	}
	if (ft_strncmp(data->map_info.global[2], "WE", 2) == 0)
	{
		i = 2;
		j = 0;
		len = 0;
		temp = NULL;
		while (data->map_info.global[2][i] != '\0' && data->map_info.global[2][i] == ' ')
			i++;
		while (data->map_info.global[2][i] !='\0')
		{
			
			len++;
			i++;
		}
		temp = malloc(sizeof(char) * (len));
		i = i - len;
		while (data->map_info.global[2][i] != '\0')
		{
			temp[j] = data->map_info.global[2][i];
			i++;
			j++;
		}
		temp[j - 1] = '\0';
		data->texture.Wwall_path = ft_strdup(temp);
		free(temp);
	}
	if (ft_strncmp(data->map_info.global[3], "EA", 2) == 0)
	{
		i = 2;
		j = 0;
		len = 0;
		temp = NULL;
		while (data->map_info.global[3][i] != '\0' && data->map_info.global[3][i] == ' ')
			i++;
		while (data->map_info.global[3][i] !='\0')
		{
			
			len++;
			i++;
		}
		temp = malloc(sizeof(char) * (len));
		i = i - len;
		while (data->map_info.global[3][i] != '\0')
		{
			temp[j] = data->map_info.global[3][i];
			i++;
			j++;
		}
		temp[j - 1] = '\0';
		data->texture.Ewall_path = ft_strdup(temp);
		free(temp);
	}

	if (check_path(data) == 1)
	{
		printf("Error : Texture Path. ABORTING\n");
		exit(0);
	}
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
	
    data->texture.ceiling.img_char = mlx_get_data_addr(data->texture.ceiling.img_ptr, &data->texture.ceiling.bits_pix, &data->texture.ceiling.len, &data->texture.ceiling.endian);
    data->texture.ceiling.global_color = blend_color(&data->texture.ceiling);
}
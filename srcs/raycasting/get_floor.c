/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_floor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leoherna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 12:01:48 by leoherna          #+#    #+#             */
/*   Updated: 2024/09/25 12:01:48 by leoherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"


int is_digit_part(char *floor_code)
{
	int i;

	i = 0;
	if (floor_code == NULL)
		return (1);
	printf("floor code : [%s]\n", floor_code);
	while(floor_code[i] != '\0')
	{
		if (ft_strchr(floor_code[i], " 0123456789,") == 0)
			return (printf("i = %d\n", i), 1);

		i++;
		if (floor_code[i] == 0)
			return (0);
	}
	return (0);
}

unsigned int rgb_to_hex(unsigned int r, unsigned int g, unsigned int b)
{
	// Assure-toi que les valeurs sont bien dans la plage [0, 255]
	if (r > 255) r = 255;
	if (g > 255) g = 255;
	if (b > 255) b = 255;

	// Combine les trois composantes dans une valeur hexadécimale
	unsigned int hexValue = (r << 16) | (g << 8) | b;
	return hexValue;
}


void get_rgb_value(t_data *data, char	*floor_color_digit)
{
	int i = 0;

	data->texture.r = ft_atoi(floor_color_digit);
	while (ft_isdigit(floor_color_digit[i]) && floor_color_digit[i] != '\0' && floor_color_digit[i] != ',')
	{
		floor_color_digit[i] = 32;
		i++;
	}
	floor_color_digit[i] = 32;
	data->texture.g = ft_atoi(floor_color_digit);
	i++;
	while (ft_isdigit(floor_color_digit[i]) && floor_color_digit[i] != '\0' && floor_color_digit[i] != ',')
	{
		floor_color_digit[i] = 32;
		i++;
	}
	floor_color_digit[i] = 32;
	data->texture.b = ft_atoi(floor_color_digit);
}

int search_floor_color(t_data *data)
{
	char	*floor_color_digit;

	floor_color_digit = find_arg(data, "F");
	printf("floor _ color -> %s\n", floor_color_digit);
	if (floor_color_digit == NULL)
		return (printf("Error 1 : Floor Digit Invalid. ABORTING\n"), free(floor_color_digit), 1);
	if (is_digit_part(floor_color_digit) == 1)
		return (printf("Error 2 : Floor Digit Invalid. ABORTING\n"), free(floor_color_digit), 1);
	get_rgb_value(data, floor_color_digit);

	if (data->texture.r > 255 || data->texture.g > 255 || data->texture.b > 255)
	{
		printf("Error 3 : Floor Digit Invalid. ABORTING\n");
		return(free(floor_color_digit), 1);
	}
	if (data->texture.r < 0 || data->texture.g < 0 || data->texture.b < 0)
	{
		printf("Error 4 : Floor Digit Invalid. ABORTING\n");	
		return(free(floor_color_digit), 1);
	}
	data->texture.floor_color = rgb_to_hex(data->texture.r, data->texture.g, data->texture.b);
	data->texture.r = 0;
	data->texture.g = 0;
	data->texture.b = 0;
	return (free(floor_color_digit), 0);
}

int search_ceiling_color(t_data *data)
{
	char	*ceiling_color_digit;

	ceiling_color_digit = find_arg(data, "C");
	if (ceiling_color_digit == NULL)
		return (2);//peut etre faut free sah
	if (is_digit_part(ceiling_color_digit) == 1)
		return (free(ceiling_color_digit), 1);
	get_rgb_value(data, ceiling_color_digit);
	if (data->texture.r > 255 || data->texture.g > 255 || data->texture.b > 255)
	{
		return (free(ceiling_color_digit), 2);
	}
	if (data->texture.r < 0 || data->texture.g < 0 || data->texture.b < 0)
	{
		return (free(ceiling_color_digit), 2);
	}
	data->texture.ceiling_color = rgb_to_hex(data->texture.r, data->texture.g, data->texture.b);
	return (free(ceiling_color_digit), 0);
}
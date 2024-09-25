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
	while(floor_code[i] != '\0')
	{
		if (ft_strchr(floor_code[i], " 0123456789,") == 0)
			return (1);
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
	printf("r-- %d\n", data->texture.r);
	printf("g-- %d\n", data->texture.g);
	printf("b-- %d\n", data->texture.b);
}

int search_floor_color(t_data *data)
{
	char	*floor_color_digit;


	floor_color_digit = find_arg(data, "F");
	if (floor_color_digit == NULL)
		return (printf("Error : Floor Digit Invalid. ABORTING\n"), free(floor_color_digit), 1);
	if (is_digit_part(floor_color_digit) == 1)
		return (printf("Error : Floor Digit Invalid. ABORTING\n"), free(floor_color_digit), 1);
	printf("les digits : %s\n", floor_color_digit);
	get_rgb_value(data, floor_color_digit);
	printf("r-- %d\n", data->texture.r);
	printf("g-- %d\n", data->texture.g);
	printf("b-- %d\n", data->texture.b);
	if (data->texture.r > 255 || data->texture.g > 255 || data->texture.b > 255)
	{
		printf("Error : Floor Digit Invalid. ABORTING\n");
		free(floor_color_digit);
		exit_manager(data);
	}
	if (data->texture.r < 0 || data->texture.g < 0 || data->texture.b < 0)
	{
		printf("Error : Floor Digit Invalid. ABORTING\n");
		free(floor_color_digit);
		exit_manager(data);
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
		return (free(ceiling_color_digit), 1);
	if (is_digit_part(ceiling_color_digit) == 1)
		return (free(ceiling_color_digit), 1);
	
	printf("les digits : %s\n", ceiling_color_digit);
	get_rgb_value(data, ceiling_color_digit);
	printf("r-- %d\n", data->texture.r);
	printf("g-- %d\n", data->texture.g);
	printf("b-- %d\n", data->texture.b);
	if (data->texture.r > 255 || data->texture.g > 255 || data->texture.b > 255)
	{
		return (1);
	}
	if (data->texture.r < 0 || data->texture.g < 0 || data->texture.b < 0)
	{
		return (1);
	}
	data->texture.ceiling_color = rgb_to_hex(data->texture.r, data->texture.g, data->texture.b);
	return (free(ceiling_color_digit), 0);
}
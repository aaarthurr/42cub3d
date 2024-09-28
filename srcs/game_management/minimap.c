// HEADER

#include "cubed.h"

int	is_wall_from_player(t_data *data, double x, double y)
{
	double	m_x;
	double	m_y;

	m_x = data->player.posX + x;
	m_y = data->player.posY + y;
	if (m_x < 0 || m_y < 0)
		return (1);
	if (data->map_info.height < m_y)
		return (1);
	if (ft_strlen(data->map_info.map[(int)(m_y)]) < m_x)
		return (1);
	if (ft_strchr(data->map_info.map[(int)(m_y)][(int)(m_x)], " 1\n\0") == 1)
		return(1);
	return (0);
}

int	is_item_from_player(t_data *data, double x, double y)
{
	double	m_x;
	double	m_y;
	int		i;
	
	m_x = floor((data->player.posX + x) * 10) / 10;
	m_y = floor((data->player.posY + y) * 10) / 10;
	i = 0;
	while (i < data->sprite.number)
	{
		//printf("DEBUG [%f, %f] <-> [%f, %f]\n", m_x, m_y, data->sprite.pills[i].x, data->sprite.pills[i].y);
		if (data->sprite.pills[i].x == m_x && data->sprite.pills[i].y == m_y &&
				data->sprite.pills[i].taken == 0 && data->sprite.pills[i].x != 0)
		{
			printf("a pill is here!!\n");
			return (1);
		}
		i++;
	}
	return (0);
}

void	draw_player_mini_map(t_data *data)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (x < 6)
	{
		y = 0;
		while (y < 6)
		{
			pixel_put_opti(&(data->img), x + 62, y + 62, 0xFF2222);
			y++;
		}
		x++;
	}
	x = 0;
}

void	draw_carre_mini_map(t_data *data, int pos_x, int pos_y)
{
	int x;
	int y;

	x = -2;
	y = -2;
	while (x < 2)
	{
		y = -2;
		while (y < 2)
		{
			pixel_put_opti(&(data->img), x + pos_x, y + pos_y, 0x22FF22);
			y++;
		}
		x++;
	}
	x = 0;
}

void	draw_item_on_map(t_data *data)
{
	double	x;
	double	y;

	x = -6;
	y = -6;
	while (x < 6)
	{
		y = -6;
		while (y < 6)
		{
			if (is_item_from_player(data, x, y) == 1)
				draw_carre_mini_map(data, (int)(x * 10) + 65, (int)(y * 10 + 65));
			y += 0.1;
		}
		x += 0.1;
	}
}

void	print_map(t_data *data)
{
	double	x;
	double	y;

	x = -6;
	y = -6;
	while (x < 6)
	{
		y = -6;
		while (y < 6)
		{
			if (is_wall_from_player(data, x, y) == 1)
				pixel_put_opti(&(data->img), (int)(x * 10) + 65, (int)((y * 10) + 65), 0x000000);
			else
				pixel_put_opti(&(data->img), (int)(x * 10) + 65, (int)((y * 10) + 65), 0xFFFFFF);
			y += 0.1;
		}
		x += 0.1;
	}
	draw_item_on_map(data);
	draw_player_mini_map(data);
	
}

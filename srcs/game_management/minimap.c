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
				pixel_put_opti(&(data->img), (int)(x * 10) + 65, (int)(y * 10 + 65), 0x000000);
			else
				pixel_put_opti(&(data->img), (int)(x * 10) + 65, (int)(y * 10 + 65), 0xFFFFFF);
			y += 0.1;
		}
		x += 0.1;
	}
	draw_player_mini_map(data);
}
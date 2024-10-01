char	**duplicata_map(t_data *data)
{
	char	**map;
	int		nb_line;
	int		x;
	int		y;

	x = 0;
	y = 0;
	data->map_info.height = count_line(data->map_info.map);
	nb_line = data->map_info.height;
	map = malloc(sizeof(char *) * (data->map_info.height + 1));
	while (y != nb_line)
	{
		map[y] = malloc(sizeof(char) * (ft_strlen(data->map_info.map[y]) + 1));
		if (!map[y])
			return (NULL);
		while (data->map_info.map[y][x] != '\0' && data->map_info.map[y][x] != '\n')
		{
			map[y][x] = data->map_info.map[y][x];
			x++;
		}
		map[y][x] = '\0';
		x = 0;
		y++;
	}
	map[y] = NULL;
	return (map);
}
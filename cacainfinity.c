

int	try_up_down(t_data *data, t_actpos act, int *top, t_pos *pos, char **map)
{
	if (map[act.act_y + 1][act.act_x] != '1'
		&& map[act.act_y + 1][act.act_x] != '2')
	{
		pos[*top].y = act.act_y + 1;
		pos[*top].x = act.act_x;
		if (should_i_be_here(1, act, map, data) == 1)
			return (1);
		map[act.act_y + 1][act.act_x] = '2';
		++*top;
	}
	if (map[act.act_y - 1][act.act_x] != '1'
		&& map[act.act_y - 1][act.act_x] != '2')
	{
		pos[*top].y = act.act_y - 1;
		pos[*top].x = act.act_x;
		if (should_i_be_here(2, act, map, data) == 1)
			return (1);
		map[act.act_y - 1][act.act_x] = '2';
		++*top;
	}
	return (0);
}

int	try_left_right(t_data *data, t_actpos act, int *top, t_pos *pos, char **map)
{
	if (map[act.act_y][act.act_x + 1] != '1'
		&& map[act.act_y][act.act_x + 1] != '2')
	{
		pos[*top].y = act.act_y;
		pos[*top].x = act.act_x + 1;
		if (should_i_be_here(3, act, map, data) == 1)
			return (1);
		map[act.act_y][act.act_x + 1] = '2';
		++*top;
	}
	if (map[act.act_y][act.act_x - 1] != '1'
		&& map[act.act_y][act.act_x - 1] != '2')
	{
		pos[*top].y = act.act_y;
		pos[*top].x = act.act_x - 1;
		if (should_i_be_here(4, act, map, data) == 1)
			return (1);
		map[act.act_y][act.act_x - 1] = '2';
		++*top;
	}
	return (0);
}
int	path_finding(t_data *data)
{
	int			top;
	t_pos		pos[1024];
	t_actpos	act;
	char		**map;

	map = duplicata_map(data);
	if (!map)
		return (1);
	top = 1;
	act.act_x = 0;
	act.act_y = 0;
	pos[0].x = data->player.IntposX;
	pos[0].y = data->player.IntposY;
	while (top > 0)
	{
		top--;
		act.act_x = pos[top].x;
		act.act_y = pos[top].y;
		if (try_up_down(data, act, &top, pos, map) == 1)
			return (path_free_map(data, map), 1);
		if (try_left_right(data, act, &top, pos, map) == 1)
			return (path_free_map(data, map), 1);
	}
	path_free_map(data, map);
	return (0);
}
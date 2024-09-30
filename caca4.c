void	copy_file(t_map_info *map_info)
{
	int		fd;
	int		j;
	char	*temp;

	j = 0;
	map_info->height = 0;
	fd = open(map_info->map_path, O_RDONLY);
	temp = get_next_line(fd);
	while (temp != NULL)
	{
		free(temp);
		map_info->height = map_info->height + 1;
		temp = get_next_line(fd);
	}
	free(temp);
	close(fd);
	map_info->global = malloc(sizeof(char *) * (map_info->height + 1));
	fd = open(map_info->map_path, O_RDONLY);
	while (j < map_info->height)
	{
		map_info->global[j] = get_next_line(fd);
		j++;
	}
	map_info->global[j] = NULL;
	map_info->global_len = j;
	close(fd);
}
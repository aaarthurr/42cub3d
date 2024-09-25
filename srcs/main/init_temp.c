/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_temp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leoherna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 09:36:25 by leoherna          #+#    #+#             */
/*   Updated: 2024/09/25 09:36:25 by leoherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

int	strlen_special(char *cum)
{
	int	i;

	i = 0;
	while (cum[i] != '\n' && cum[i] != '\0')
	{
		i++;
	}
	return (i);
}

int	count_line(int fd, t_var *var)
{
	char	*line;
	int		nb_line;

	nb_line = 0;
	line = NULL;
	while (line || nb_line == 0)
	{
		if (line)
		{
			nb_line++;
			if (nb_line == 1)
				var->len = strlen_special(line);
			if (var->len != strlen_special(line))
				return (free(line), close(fd),
					write(1, "Error\n", 6), get_next_line(-1), -1);
			free(line);
			line = NULL;
		}
		line = get_next_line(fd);
	}
	close(fd);
	return (nb_line);
}

int	get_map(t_data *data, int fd)
{
	int		nb_line;
	int		i;

	nb_line = count_line(fd, var);
	if (nb_line == -1)
		exit (1);
	fd = open(map, O_RDONLY);
	if (fd == -1 || read(fd, &line, 0) < 0)
		exit(1);
	i = 0;
	var->map = malloc(sizeof(char *) * (nb_line + 1));
	while (i != nb_line)
	{
		var->map[i] = get_next_line(fd);
		i++;
		if (var->map[i] == NULL)
			break ;
	}
	var->map[i] = NULL;
	get_next_line(-1);
	return (nb_line);
}


void	get_all(char **argv, t_data *data)
{
	if (check_file(argv[1]) )
		return;
	data->map_info.map_path = argv[1];
    copy_file(&data->map_info);
    get_map(data);
	print_tab(data->map_info.map);
}
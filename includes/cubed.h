/* ************************************************************************** */
/*															 */
/*											 :::	 ::::::::   */
/*   cubed.h									:+:	 :+:	:+:   */
/*										  +:+ +:+		+:+	*/
/*   By: leoherna <marvin@42.fr>				+#+  +:+	  +#+	   */
/*									   +#+#+#+#+#+   +#+		 */
/*   Created: 2024/04/16 15:03:08 by arpages		 #+#	#+#		   */
/*   Updated: 2024/04/23 13:53:17 by leoherna		###   ########.fr	  */
/*															 */
/* ************************************************************************** */

#ifndef CUBED_H
# define CUBED_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>

# include "get_next_line.h"
#include "../minilibx/mlx.h"

typedef struct map_info_s
{
	char *map_path;
	char **global;
	char **info;
	char **map;
	int height;
}			t_map_info;

typedef struct ray_s
{
	float x;
	float y;
		
}			t_ray;

typedef struct data_s
{
	void		*mlx;
	void		*win;
	int			win_height;
	int			win_width;
	
	t_map_info  map_info;
	t_ray		ray;
}				t_data;

/* main */
//main.c

//init.c
void	copy_file(t_map_info *map_info);
void	get_map(t_map_info *map_info);
int		is_map_part(char *line);


/* utils */
//tools.c
int		ft_strlen(char *str);
int		tab_size(char **tab);
void	print_tab(char **tab);
char	**tab_realloc(char **tab, int m_size, char *content);

#endif
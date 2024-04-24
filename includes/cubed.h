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
# include <math.h>

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

typedef struct s_ray
{
	float x;
	float y;
		
}			t_ray;

typedef struct s_player
{
	//vecteur position
	double	posX;
	double	posY;
	//direction du joueur
	int dirX;
	int dirY;
	//plan de la camera
	int planX;
	int	planY;
}			t_player;

typedef struct data_s
{
	void		*mlx;
	void		*win;
	int			win_height;
	int			win_width;
	t_player	player;
	t_map_info  map_info;
	t_ray		ray;
}				t_data;

/*------srcs/main/game_manager------*/
int     game_manager(t_data *data);

/*------srcs/main/init-----*/
void	get_all(char **argv, t_data *data);
void	copy_file(t_map_info *map_info);
void	get_map(t_map_info *map_info);
int		is_map_part(char *line);

/*------srcs/main/checker.c-----*/
int		check_map(t_data *data);
int		check_file(char *str);

/*------srcs/map/map_checker*/
int		check_walls(t_data *data);
int		check_walls_bis(t_data *data, int x, int y);

void	set_pos(t_data *data, int x, int y);

/*------srcs/main/error.c-----*/
void	error_manager(char *line, int code);

/*------srcs/raycasting/raycasting.c---*/
void    raycasting(t_data *data);

/*------srcs/utils/free_manager----- */
void    free_mapinfo(t_data *data);
void    free_tab(char **tab);

/*------srcs/utils/tools*/
void	print_tab(char **tab);
char	**tab_realloc(char **tab, int m_size, char *content);
int		tab_size(char **tab);


/*--------srcs/utils/ft_tools.c*/
int		ft_strlen(char *str);
int		ft_strchr(char c, char *str);
int		ft_strncmp(const char *str1, const char *str2, unsigned int n);

#endif
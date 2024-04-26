/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leoherna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:29:44 by leoherna          #+#    #+#             */
/*   Updated: 2024/04/26 15:42:29 by leoherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cubed.h"

#define GRID_SIZE 20
#define KEY_ESC 65307
#define KEY_A 97
#define KEY_D 100
#define KEY_S 115
#define KEY_W 119
#define KEY_LEFT 65361
#define KEY_RIGHT 65363
#define CELL_SIZE 50

void draw_circle(t_data *data) 
{
    int cell_x = (int)(data->player.posX * CELL_SIZE); // Coordonnée x de la case
    int cell_y = (int)(data->player.posY* CELL_SIZE); // Coordonnée y de la case
    int draw_x = cell_x + CELL_SIZE / 2; // Centre x du cercle dans la case
    int draw_y = cell_y + CELL_SIZE / 2; // Centre y du cercle dans la case
    int i, j;

    // Afficher un cercle rouge au centre de la case
    for (i = draw_x - 10; i <= draw_x + 10; ++i) {
        for (j = draw_y - 10; j <= draw_y + 10; ++j) {
            int dx = i - draw_x;
            int dy = j - draw_y;
            if (dx * dx + dy * dy <= 100) {
                mlx_pixel_put(data->mlx, data->win, i, j, 0x000000); // Rouge
            }
        }
    }
    double end_x = draw_x + data->player.dirX * 25; // Coordonnée x de l'extrémité du trait
    double end_y = draw_y + data->player.dirY * 25; // Coordonnée y de l'extrémité du trait

    // Dessiner la ligne pixel par pixel
    double dx = end_x - draw_x;
    double dy = end_y - draw_y;
    double length = sqrt(dx * dx + dy * dy); // Longueur de la ligne
    dx /= length; // Normaliser le vecteur direction x
    dy /= length; // Normaliser le vecteur direction y

    // Dessiner la ligne pixel par pixel
    for (double t = 0; t < length; ++t) {
        int pixel_x = (int)(draw_x + dx * t);
        int pixel_y = (int)(draw_y + dy * t);
        mlx_pixel_put(data->mlx, data->win, pixel_x, pixel_y, 0x000000); // Noir
    }
}
void printcase(t_data *data, int i, int j, int color)
{
    int x;
    int y;
    int count;
    int count2;

    count=0;
    count2=0;
    x = i * 50;
    y = j * 50;
    while (count != 49)
    {
        while (count2 != 49)
        {
            mlx_pixel_put(data->mlx, data->win, x, y, color);
            x++;
            count2++;
        }
        count2 = 0;
        count++;
        x = i * 50;
        y++;
    }
    
}
void    printcase_where_0(t_data *data, char **map)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (map[j])
    {
        while (map[j][i] != '\0')
        {
            if (map[j][i] == '0' || map[j][i] == 'S')
            {
                printcase(data, i, j, 0xFFFFFF);
            }
            i++;
        }
        i = 0;
        j++;
    }

}
void    printcase_where_1(t_data *data, char **map)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (map[j])
    {
        while (map[j][i] != '\0')
        {
            if (map[j][i] == '1')
            {
                printcase(data, i, j, 0x00FFFF);
            }
            i++;
        }
        i = 0;
        j++;
    }

}

void draw_line(int x0, int y0, int x1, int y1, void *mlx_ptr, void *win_ptr)
{
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx, sy;

    if (x0 < x1) sx = 1;
    else sx = -1;
    if (y0 < y1) sy = 1;
    else sy = -1;

    int err = dx - dy;
    int e2;

    while (!(x0 == x1 && y0 == y1)) {
        mlx_pixel_put(mlx_ptr, win_ptr, x0, y0, 0xFFFFFF); // Dessiner le pixel
        e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
}

void draw_grid(t_data *data, char **map)
{
    int x;
    int y;
    int i;

    i = 0;
    x = 1;
    y = 1;
    while (y <= (tab_size(map)) * 50 + 1)
    {
        while (x <= (ft_strlen(map[i])- 1) * 50 + 1)
        {
            mlx_pixel_put(data->mlx, data->win, x, y, 0x00FF00);
            x++;
        }
        x = 1;
        y += 50;
    }
    x = 1;
    y = 1;
    while (x <= (ft_strlen(map[i])- 1) * 50  + 1)
    {
        while (y <= (tab_size(map)) * 50 + 1)
        {
            mlx_pixel_put(data->mlx, data->win, x, y, 0x00FF00);
            y++;
        }
        y = 1;
        x += 50;
    }
    printcase_where_1(data, map);
    printcase_where_0(data, map);
    draw_circle(data);
}
int     close_window(t_data *data)
{
        //free_player(data);
        free_mapinfo(data);
        mlx_destroy_window(data->mlx, data->win);
        mlx_destroy_display(data->mlx);
        free(data->mlx);
        exit(0);
}


int     event(int keycode, t_data *data)
{
    

    



    /*for (int i =0; i++; i= 500)
    {
        int negger = (data->win_height / 2) + data->player.dirX * 100;
        int neggus = (data->win_width / 2) + data->player.dirY * 100;
        draw_line(data->win_height / 2, data->win_width / 2, negger, neggus , data->mlx, data->win);
        rotate_player(data, 0.001);
    }*/
	printf("%d\n", keycode);
    
 
    if (keycode == KEY_ESC)
        close_window(data);
    if (keycode == KEY_S)
    {
        move_player(data, 0, 0.1);
    }
    if (keycode == KEY_W)
    {
        move_player(data, 0, -0.1);
    }
    if (keycode == KEY_A)
    {
       move_player(data, -0.1, 0);
    }
    if (keycode == KEY_D)
    {
        move_player(data, 0.1, 0);
    }
	if (keycode == KEY_LEFT)
		rotate_player(data, 0.2);
	if (keycode == KEY_RIGHT)
		rotate_player(data, -0.2);
    draw_grid(data, data->map_info.map);
    draw_circle(data);
	
	printf("%f , %f [%f, %f]\n", data->player.posX, data->player.posY, data->player.dirX, data->player.dirY);
    return (0);
}

void move_player(t_data *data, double x, double y)
{
    data->player.posX += x;
    data->player.posY += y;

}
void rotate_player(t_data *data, double angle)
{
	double c_x;
	double c_y;

	c_x = data->player.dirX;
	c_y = data->player.dirY;
	data->player.dirX = (c_x * cos(angle)) - (c_y * sin(angle));
	data->player.dirY = (c_x * sin(angle)) + (c_y * cos(angle));
}





int     game_manager(t_data *data)
{
    data->win_height = 480;
	data->win_width = 640;
    data->player.posX = 1.5;
    data->player.posY = 1.5;
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, data->win_height, data->win_height, "Backroom cub3d"); 


    //raycasting(data);
    printf("%d\n",tab_size(data->map_info.map));
    draw_grid(data, data->map_info.map);
    draw_circle(data);
  
    //mlx_mouse_hook(data->win, mouse_move, &data);
    mlx_key_hook(data->win, event, data);
	mlx_loop(data->mlx);
    return (0);
}
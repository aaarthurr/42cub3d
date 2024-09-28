/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mob.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leoherna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 10:56:18 by leoherna          #+#    #+#             */
/*   Updated: 2024/09/25 10:56:18 by leoherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

typedef struct {
    double dist;
    int order;
} Sprite;

int compareSprites(const void* a, const void* b) 
{
    Sprite* spriteA = (Sprite*)a;
    Sprite* spriteB = (Sprite*)b;
    
    if (spriteA->dist < spriteB->dist) return 1;  // Inverser l'ordre pour trier du plus grand au plus petit
    if (spriteA->dist > spriteB->dist) return -1;
    return 0;
}

void sort_sprite(int* order, double* dist, int amount)
{
    Sprite* sprites = (Sprite*)malloc(amount * sizeof(Sprite));
    if (sprites == NULL) {
        printf("Erreur d'allocation mémoire.\n");
        return;
    }
    for (int i = 0; i < amount; i++)
	{
        sprites[i].dist = dist[i];
        sprites[i].order = order[i];
    }
    qsort(sprites, amount, sizeof(Sprite), compareSprites);
    for (int i = 0; i < amount; i++)
	{
        dist[i] = sprites[i].dist;
        order[i] = sprites[i].order;
    }
    free(sprites);
}


void	draw_sprite_line(t_data *data, t_spritestate *sp)
{
	int stripe;
	int y;
	int texX;

	stripe = sp->drawStartX;
	while (stripe < sp->drawEndX)
	{
		texX = (int)((256* (stripe - (-sp->spriteWidth / 2 + sp->spriteScreenX)) * SPRITE_SIZE / sp->spriteWidth) / 256);
		y = sp->drawStartY;
		if (sp->transformY > 0 && stripe > 0 && stripe < data->win_width && sp->transformY < data->sprite.Zbuffer[stripe])
		{
			while (y < sp->drawEndY)
			{
				int d = (y) * 256 - data->win_height * 128 + sp->spriteHeight * 128;
				int texY = ((d * SPRITE_SIZE) / sp->spriteHeight) / 256;
				int color = get_pixel_color(&(data->texture.pills), texX, texY);
				if (color > 0)
					pixel_put_opti(&(data->img), stripe, y, color);
				y++;
			}
		}
		stripe++;
	}
}

void	draw_sprite(t_data *data, int *spriteOrder, int i)
{
	t_spritestate sp;

	sp.spriteX = data->sprite.pills[spriteOrder[i]].x - data->player.posX;
	sp.spriteY = data->sprite.pills[spriteOrder[i]].y - data->player.posY;
	sp.invDet = 1.0 / (data->player.planX * data->player.dirY - data->player.dirX * data->player.planY);
	sp.transformX = sp.invDet * (data->player.dirY * sp.spriteX - data->player.dirX * sp.spriteY);
	sp.transformY = sp.invDet * (-data->player.planY * sp.spriteX + data->player.planX * sp.spriteY);
	sp.spriteScreenX = (int)((data->win_width / 2) * (1 + sp.transformX / sp.transformY));
	sp.spriteHeight = abs((int)(data->win_height / sp.transformY));
	sp.drawStartY = -(sp.spriteHeight) / 2 + data->win_height / 2;
	sp.drawEndY = sp.spriteHeight / 2 + data->win_height / 2;
	if (sp.drawStartY < 0)
		sp.drawStartY = 0;
	if (sp.drawEndY	>= data->win_height)
		sp.drawEndY = data->win_height - 1;
	sp.spriteWidth = abs((int)(data->win_height / sp.transformY));
	sp.drawStartX = -(sp.spriteWidth) / 2 + sp.spriteScreenX;
	sp.drawEndX = sp.spriteWidth / 2 + sp.spriteScreenX;
	if (sp.drawStartX < 0)
		sp.drawStartX = 0;
	if (sp.drawEndX	>= data->win_width)
		sp.drawEndX = data->win_width - 1;
	draw_sprite_line(data, &sp);
}

void	cast_sprite(t_data *data)
{
	int i;

	int *spriteOrder;
	double *spriteDistance;
	
	spriteOrder = malloc(sizeof(int) * data->sprite.number);
	spriteDistance = malloc(sizeof(double) * data->sprite.number);

	i = 0;
	while (i < data->sprite.number)
	{
		spriteOrder[i] = i;
		spriteDistance[i] = ((data->player.posX - data->sprite.pills[i].x) * (data->player.posX - data->sprite.pills[i].x) + (data->player.posY - data->sprite.pills[i].y) * (data->player.posY - data->sprite.pills[i].y));
		i++;
	}
	sort_sprite(spriteOrder, spriteDistance, data->sprite.number);
	for (int x = 0; x < data->sprite.number; x++)
		printf("--> %f is at rank %d  [index %d]\n", spriteDistance[spriteOrder[x]], spriteOrder[x], x);
	i = 0;
	printf("--------------\n");
	while (i < data->sprite.number)
	{
		if (spriteDistance[spriteOrder[i]] < 0.5 && data->sprite.pills[spriteOrder[i]].taken == 0)
		{
			take_drugs(data);
			data->sprite.pills[spriteOrder[i]].taken = 1;
		}
		if (data->sprite.pills[spriteOrder[i]].taken == 0)
		{
			printf("printing an item at distance -> %f\n", spriteDistance[spriteOrder[i]]);
			draw_sprite(data, spriteOrder, i);
		}
		i++;
	}
}

int		is_a_pill_here(t_data *data, float x, float y)
{
	int	i;

	i = 0;
	while (i < data->sprite.number)
	{
		if (data->sprite.pills[i].x == x + 0.5 && data->sprite.pills[i].y == y + 0.5)
		{
			return(1);
		}
		i++;
	}
	return(0);
}

void	init_pills(t_data *data)
{
	int i;

	i = 0;
	while (i < data->sprite.number)
	{
		data->sprite.pills[i].x = 0;
		data->sprite.pills[i].y = 0;
		data->sprite.pills[i].taken = 0;
		printf("No %d\n", i);
		i++;
	}
}

int    set_items_coordonnates(t_data *data, t_pills *pill)
{
    int i;
	int	j;
	int cap;

	cap = 0;
	i = 0;
	j = 0;
	while (data->map_info.map[i][j] != '0' && cap < 25)
	{
		i = rand() % data->map_info.height;
		j = rand() % ft_strlen(data->map_info.map[i]);
		cap++;
		if (data->map_info.map[i][j] == '0' && is_a_pill_here(data, j, i) == 0)
		{
			pill->y = i + 0.5;
			pill->x = j + 0.5;
			return(0);
		}
	}
	return(1);
}

t_pills	*set_up_items(t_data *data, int number)
{
	t_pills *pills;
	int		i;

	i = 0;
	pills = malloc(sizeof(t_pills) * number);
	data->sprite.pills = pills;
	init_pills(data);
	while (i < number)
	{
		set_items_coordonnates(data, &(pills[i]));
		printf("---> placed pill no%d at (%f, %f)\n",i, pills[i].x, pills[i].y);
		i++;
	}
	return pills;
}

void	set_sprite(t_data *data, int number)
{
	data->sprite.number = number;
	data->sprite.Zbuffer = malloc(sizeof(double) * data->win_width);
	data->sprite.pills = set_up_items(data, number);
}
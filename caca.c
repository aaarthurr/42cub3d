//cet endroit sert au fonction que jai remplace par une version avec la norme


void	draw_sprite_line(t_data *data, t_spritestate *sp)
{

	int		stripe;
	double	y;
	int		texX;
	int		d;
	int		texY;
	int		color;

	stripe = sp->drawStartX;
	while (stripe < sp->drawEndX)
	{
		texX = (int)((256* (stripe - (-sp->spriteWidth / 2 + sp->spriteScreenX)) * SPRITE_SIZE / sp->spriteWidth) / 256);
		y = sp->drawStartY;
		if (sp->transformY > 0 && stripe > 0 && stripe < data->win_width && sp->transformY < data->sprite.Zbuffer[stripe])
		{
			while (y < sp->drawEndY)
			{
				d = (y) * 256 - data->win_height * 128 + sp->spriteHeight * 128;
				texY = ((d * SPRITE_SIZE) / sp->spriteHeight) / 256;
				color = get_pixel_color(&(data->texture.pills), texX, texY);
				if (color > 0)
					pixel_put_opti(&(data->img), stripe, y, color);
				y++;
			}
		}
		stripe++;
	}
}




void	cast_sprite(t_data *data)
{
	int		i;
	int		*spriteOrder;
	double	*spriteDistance;

	spriteOrder = malloc(sizeof(int) * data->sprite.number);
	spriteDistance = malloc(sizeof(double) * data->sprite.number);
	i = 0;
	while (i < data->sprite.number)
	{
		spriteOrder[i] = i;
		data->sprite.pills[i].index = i;
		spriteDistance[i] = ((data->player.posX - data->sprite.pills[i].x) *
				(data->player.posX - data->sprite.pills[i].x) +
				(data->player.posY - data->sprite.pills[i].y) *
				(data->player.posY - data->sprite.pills[i].y));
		data->sprite.pills[i].distance = spriteDistance[i];
		i++;
	}
	sort_sprite(spriteOrder, spriteDistance, data->sprite.number);
	i = 0;
	while (i < data->sprite.number)
	{
		if (data->sprite.pills[spriteOrder[i]].distance < 0.5 && data->sprite.pills[spriteOrder[i]].taken == 0)
		{
			take_drugs(data);
			data->sprite.pills[spriteOrder[i]].taken = 1;
		}
		if (data->sprite.pills[spriteOrder[i]].taken == 0)
			draw_sprite(data, spriteOrder, i);
		i++;
	}
	free(spriteDistance);
	free(spriteOrder);
}
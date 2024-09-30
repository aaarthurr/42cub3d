
void	draw_sprite_line(t_data *data, t_spritestate *sp)
{
	t_var	var;
	int		stripe;
	double	y;
	int		d;

	stripe = sp->drawStartX;
	while (stripe < sp->drawEndX)
	{
		var.x = (int)((256 * (stripe - (-sp->spriteWidth / 2
							+ sp->spriteScreenX))
					* SPRITE_SIZE / sp->spriteWidth) / 256);
		y = sp->drawStartY;
		if (sp->transformY > 0 && stripe > 0 && stripe < data->win_width
			&& sp->transformY < data->sprite.Zbuffer[stripe])
		{
			while (y < sp->drawEndY)
			{
				d = (y) * 256 - data->win_height * 128 + sp->spriteHeight * 128;
				var.y = ((d * SPRITE_SIZE) / sp->spriteHeight) / 256;
				var.c = get_pixel_color(&(data->texture.pills), var.x, var.y);
				if (var.c > 0)
					pixel_put_opti(&(data->img), stripe, y, var.c);
				y++;
			}
		}
		stripe++;
	}
}

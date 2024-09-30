

void drawverticalline_bis(t_data *data,t_raystate *raystate, t_var *var, t_img *img)
{
   	while (var->y < var->lend)
	{
		var->x = (int)var->d_b & (TEX_SIZE - 1);
		var->d_b += var->d_a;
		var->c = get_pixel_color(img, raystate->texX, var->x);
		var->c = assombrircouleur(var->c, raystate->perpWallDist * (raystate->perpWallDist / 2));
		if (data->player.drug_level >= 9)
			var->c = give_lsd(data, var->c);
		pixel_put_opti(&(data->img), raystate->x, y, var->c);
		var->y++;
	}
	while (var->y < data->win_height)
	{
		if (data->player.drug_level < 5)
		{
			pixel_put_opti(&(data->img), raystate->x, var->y, data->texture.floor_color);
		}
		var->y++;
	}
}
void	drawverticalline(t_data *data, t_raystate *raystate, int lstart, int lend, t_img *img)
{

    t_var var;
	int		var.y;//y
	int		var.c;//color
	double	var.d_a;//step
	double	var.d_b;//tex_pos
	int		var.x;//tex y
    int     var.lstart//lstart
    int     var.lend//lend
    var.lstart = lstart;
    var.lend = lend;

	var.d_a = 1.0 * TEX_SIZE / raystate->line_height;
	var.d_b = ((var.lstart - raystate->offset) - data->win_height / 2 + raystate->line_height / 2) * var.d_a;
	var.y = 0;
	data->sprite.Zbuffer[raystate->x] = raystate->perpWallDist;
	while (var.y < var.lstart)
	{
		if (data->player.drug_level < 5)
		{
			if (data->texture.ceiling_color_or_texture == 0)
			{
				pixel_put_opti(&(data->img), raystate->x, var.y, data->texture.ceiling_color);
			}
		}
		var.y++;
	}
    drawverticalline_bis(data, raystate, &var, img);
}



void	drawverticalline(t_data *data, t_raystate *raystate, int lstart, int lend, t_img *img)
{
	int		y;
	int		color;
	double	step;
	double	tex_pos;
	int		tex_y;

	step = 1.0 * TEX_SIZE / raystate->line_height;
	tex_pos = ((lstart - raystate->offset) - data->win_height / 2 + raystate->line_height / 2) * step;
	y = 0;
	data->sprite.Zbuffer[raystate->x] = raystate->perpWallDist;
	while (y < lstart)
	{
		if (data->player.drug_level < 5)
		{
			if (data->texture.ceiling_color_or_texture == 0)
			{
				pixel_put_opti(&(data->img), raystate->x, y, data->texture.ceiling_color);
			}
		}
		y++;
	}
	while (y < lend)
	{
		tex_y = (int)tex_pos & (TEX_SIZE - 1);
		tex_pos += step;
		color = get_pixel_color(img, raystate->texX, tex_y);
		color = assombrircouleur(color, raystate->perpWallDist * (raystate->perpWallDist / 2));
		if (data->player.drug_level >= 9)
			color = give_lsd(data, color);
		pixel_put_opti(&(data->img), raystate->x, y, color);
		y++;
	}
	while (y < data->win_height)
	{
		if (data->player.drug_level < 5)
		{
			pixel_put_opti(&(data->img), raystate->x, y, data->texture.floor_color);
		}
		y++;
	}
}
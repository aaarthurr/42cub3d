



void	which_texture(t_data *data, t_raystate *raystate, int l_start, int l_end)
{
	if (raystate->side == 0 && raystate->mapX > data->player.posX)
		drawverticalline(data, raystate, l_start, l_end, &(data->texture.Ewall));
	if (raystate->side == 0 && raystate->mapX < data->player.posX)
		drawverticalline(data, raystate, l_start, l_end, &(data->texture.Wwall));
	if (raystate->side == 1 && raystate->mapY > data->player.posY)
		drawverticalline(data, raystate, l_start, l_end, &(data->texture.Swall));
	if (raystate->side == 1 && raystate->mapY < data->player.posY)
		drawverticalline(data, raystate, l_start, l_end, &(data->texture.Nwall));
}
void	drawverticalline(t_data *data, t_raystate *raystate,
	int lstart, int lend, t_img *img)
{
	t_var	var;

	var.lstart = lstart;
	var.lend = lend;
	var.d_a = 1.0 * TEX_SIZE / raystate->line_height;
	var.d_b = ((var.lstart - raystate->offset) - data->win_height
			/ 2 + raystate->line_height / 2) * var.d_a;
	var.y = 0;
	data->sprite.Zbuffer[raystate->x] = raystate->perpWallDist;
	while (var.y < var.lstart)
	{
		if (data->player.drug_level < 5)
		{
			if (data->texture.ceiling_color_or_texture == 0)
				pixel_put_opti(&(data->img),
					raystate->x, var.y, data->texture.ceiling_color);
		}
		var.y++;
	}
	drawverticalline_bis(data, raystate, &var, img);
}
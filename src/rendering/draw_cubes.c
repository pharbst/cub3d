/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_cubes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlohmann <jlohmann@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 01:53:23 by jlohmann          #+#    #+#             */
/*   Updated: 2023/05/02 19:50:34 by jlohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_point	set_line(double dist, double fov)
{
	int		line_height;
	t_point	line;

	if (dist < 0.01)
		line_height = SCREEN_HEIGHT / fov;
	else
		line_height = SCREEN_HEIGHT / dist / fov;
	line.y = -line_height / 2 + 0.75 * SCREEN_HEIGHT;
	line.x = line_height / 2 + 0.75 * SCREEN_HEIGHT;
	return (line);
}

static mlx_texture_t	*get_texture(int side, t_tex *textures)
{
	if (side == 1)
		return (textures->t_north);
	else if (side == 2)
		return (textures->t_east);
	else if (side == 3)
		return (textures->t_south);
	else
		return (textures->t_west);
}

static int	get_tex_column(int side, t_vec hit_pos, mlx_texture_t *tex)
{
	double	wall_x;
	int		tex_x;

	wall_x = hit_pos.x;
	if (side % 2 == 0)
		wall_x = hit_pos.y;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * tex->width);
	if (side == 0)
		tex_x = tex->width - tex_x - 1;
	if (side == 1)
		tex_x = tex->width - tex_x - 1;
	return (tex_x);
}

// line.x = end, line.y = start/current position
static t_tex_params	set_tex_params(t_scene *scene, t_hit_info hit, t_point line)
{
	t_tex_params	texp;

	texp.tex = get_texture(hit.side, &scene->tex);
	texp.pos.x = get_tex_column(hit.side, hit.pos, texp.tex);
	texp.pos.y = 0;
	texp.step = 1.0 * texp.tex->height / (line.x - line.y);
	if (line.y < 0)
		texp.pos.y = -line.y * texp.step;
	return (texp);
}

void	draw_wall_line(t_scene *scene, int32_t x, t_hit_info hit)
{
	t_point			line;
	t_tex_params	texp;
	t_color			color;

	line = set_line(hit.dist, scene->player.fov);
	texp = set_tex_params(scene, hit, line);
	if (texp.pos.y != 0)
		line.y = 0;
	while (line.y < line.x && line.y < 1.5 * SCREEN_HEIGHT)
	{
		if (texp.pos.y >= texp.tex->height)
			texp.pos.y = texp.tex->height - 1;
		color = get_pixel(texp.tex, texp.pos.x, texp.pos.y);
		if (hit.dist == 0)
			color = color_dim(color, 1);
		else
			color = color_dim(color, 4 / hit.dist);
		set_pixel(scene->screen, x, line.y, color);
		texp.pos.y += texp.step;
		++line.y;
	}
}

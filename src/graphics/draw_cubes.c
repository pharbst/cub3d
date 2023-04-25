/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_cubes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlohmann <jlohmann@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 01:53:23 by jlohmann          #+#    #+#             */
/*   Updated: 2023/04/25 16:01:19 by jlohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	get_line_height(double dist, int *start, int *end, double fov)
{
	int	line_height;

	if (dist == 0)
		line_height = SCREEN_HEIGHT / fov;
	else
		line_height = SCREEN_HEIGHT / dist / fov;
	*start = -line_height / 2 + 0.75 * SCREEN_HEIGHT;
	*end = line_height / 2 + 0.75 * SCREEN_HEIGHT;
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
	wall_x -= floor(wall_x); // (int)wallX?
	tex_x = (int)(wall_x * tex->width);
	if (side == 0)
		tex_x = tex->width - tex_x - 1;
	if (side == 1)
		tex_x = tex->width - tex_x - 1;
	return (tex_x);
}

static uint32_t	get_pixel(int tex_x, int tex_y, mlx_texture_t *tex)
{
	t_pixel	color;

	color.r = tex->pixels[(tex_y * tex->width + tex_x) * tex->bytes_per_pixel];
	color.g = tex->pixels[(tex_y * tex->width + tex_x) * tex->bytes_per_pixel + 1];
	color.b = tex->pixels[(tex_y * tex->width + tex_x) * tex->bytes_per_pixel + 2];
	color.a = tex->pixels[(tex_y * tex->width + tex_x) * tex->bytes_per_pixel + 3];
	return (color.pixel);
}

void	draw_wall_line(t_scene *scene, int32_t x, t_hit_info hit)
{
	int				line_start;
	int				line_end;
	mlx_texture_t	*tex;
	int				tex_x;
	double			tex_y;
	double			tex_step;
	t_pixel			color;

	get_line_height(hit.dist, &line_start, &line_end, scene->player.fov);
	tex = get_texture(hit.side, &scene->tex);
	tex_x = get_tex_column(hit.side, hit.pos, tex);
	tex_y = 0;
	tex_step = 1.0 * tex->height / (line_end - line_start);
	while (line_start < line_end)
	{
		if (line_start >= 0 && line_start < 1.5 * SCREEN_HEIGHT)
		{
			if (tex_y >= tex->height)
				tex_y = tex->height - 1;
			color.pixel = get_pixel(tex_x, tex_y, tex);
			/* if (hit.dist == 0)
				color = color_change_lightness(color, 1);
			else
				color = color_change_lightness(color, 2 / hit.dist); */
			// color.a = 0XFF;
			set_pixel(scene->screen, x, line_start, color.pixel);
		}
		tex_y += tex_step;
		++line_start;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_cubes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlohmann <jlohmann@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 01:53:23 by jlohmann          #+#    #+#             */
/*   Updated: 2023/04/21 00:53:23 by jlohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	get_line_height(double dist, int *start, int *end)
{
	int	line_height;

	if (dist == 0)
		line_height = SCREEN_HEIGHT;
	else
		line_height = SCREEN_HEIGHT / dist;
	*start = -line_height / 2 + 0.75 * SCREEN_HEIGHT;
	*end = line_height / 2 + 0.75 * SCREEN_HEIGHT;
	*start *= (*start >= 0);
	if (*end > 1.5 * SCREEN_HEIGHT)
		*end = 1.5 * SCREEN_HEIGHT;
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
	uint32_t		color;

	color = (uint32_t)tex->pixels[(tex_y * tex->width + tex_x) * tex->bytes_per_pixel] << 24;
	color |= (uint32_t)tex->pixels[(tex_y * tex->width + tex_x) * tex->bytes_per_pixel + 1] << 16;
	color |= (uint32_t)tex->pixels[(tex_y * tex->width + tex_x) * tex->bytes_per_pixel + 2] << 8;
	color |= (uint32_t)tex->pixels[(tex_y * tex->width + tex_x) * tex->bytes_per_pixel + 3];
	return (color);
}

void	draw_wall_line(mlx_image_t *screen, int32_t x, t_hit_info hit, t_tex *textures)
{
	int				line_start;
	int				line_end;
	mlx_texture_t	*tex;
	int				tex_x;
	double			tex_y;
	double			tex_step;
	uint32_t		color;

	get_line_height(hit.dist, &line_start, &line_end);
	tex = get_texture(hit.side, textures);
	tex_x = get_tex_column(hit.side, hit.pos, tex);
	tex_y = 0;
	tex_step = 1.0 * tex->height / (line_end - line_start);
	while (line_start < line_end)
	{
		if (tex_y >= tex->height)
			tex_y = tex->height - 1;
		color = get_pixel(tex_x, tex_y, tex);
		/* if (hit.dist == 0)
			color = color_change_lightness(color, 1);
		else
			color = color_change_lightness(color, 2 / hit.dist); */
		mlx_put_pixel(screen, x, line_start, color);
		tex_y += tex_step;
		++line_start;
	}
}

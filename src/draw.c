/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlohmann <jlohmann@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 12:21:07 by jlohmann          #+#    #+#             */
/*   Updated: 2023/03/29 14:16:36 by jlohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	img_fill_color(mlx_image_t *img, uint32_t color)
{
	uint32_t	x;
	uint32_t	y;

	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			mlx_put_pixel(img, x, y, color);
			++x;
		}
		++y;
	}
}

void	draw_player(struct s_player *player)
{
	img_fill_color(player->image_2d, 0x00000000);
	player->image_2d->instances[0].x = player->x - 8;
	player->image_2d->instances[0].y = player->y - 8;
	draw_point(player->image_2d, 8, 8, 4, 0x00AA00FF);
	draw_line(player->image_2d, 8, 8, 8 + player->dx * 4, 8 + player->dy * 4, 0x00AA00FF);
}

void	draw_map(struct s_scene *scene)
{
	int x;
	int	y;

	y = 0;
	while (y < scene->map.height)
	{
		x = 0;
		while(x < scene->map.width)
		{
			if (scene->map.data[y * scene->map.width + x] == 1)
				draw_rect(scene->screen, x * SPRITE_SIZE, y * SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE, 0xFFFFFFFF);
			else
				draw_rect(scene->screen, x * SPRITE_SIZE, y * SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE, 0x222222FF);
			++x;
		}
		++y;
	}
}

void	draw_rays(struct s_scene *scene)
{
	int		r, mx, my, mp, dof;
	double	rx, ry, ra, xo, yo;
	double	aTan;

	ra = scene->player.phi;
	r = 0;
	while (r < 1)
	{
		dof = 0;
		aTan = -1 / tan(ra);
		if (ra > M_PI)
		{
			ry = (((int)scene->player.y>>5)<<5) - 0.0001;
			rx = (scene->player.y - ry) * aTan + scene->player.x;
			yo = -32;
			xo = -yo * aTan;
		}
		else if (ra < M_PI)
		{
			ry = (((int)scene->player.y>>5)<<5) + 32;
			rx = (scene->player.y - ry) * aTan + scene->player.x;
			yo = 32;
			xo = -yo * aTan;
		}
		else if (ra == 0 || ra == M_PI)
		{
			rx = scene->player.x;
			ry = scene->player.y;
			dof = 16;
		}
		while (dof < 16)
		{
			mx = (int)(rx)>>5;
			my = (int)(ry)>>5;
			mp = my * scene->map.width + mx;
			if (mp < scene->map.width * scene->map.height && scene->map.data[mp] == 1)
				break ;
			rx += xo;
			ry += yo;
			++dof;
		}
		draw_line(scene->screen, scene->player.x, scene->player.y, rx, ry, 0xFFFF00FF);
		++r;
	}
	
}

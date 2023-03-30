/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlohmann <jlohmann@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 12:21:07 by jlohmann          #+#    #+#             */
/*   Updated: 2023/03/30 19:31:22 by jlohmann         ###   ########.fr       */
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
	img_fill_color(player->img, 0x00000000);
	player->img->instances[0].x = player->pos.x - 8;
	player->img->instances[0].y = player->pos.y - 8;
	draw_point(player->img, (t_point){8, 8}, 4, 0x00AA00FF);
	draw_line(player->img, (t_point){8, 8}, (t_point){8 + player->dir.x * 1.5, 8 + player->dir.y * 1.5}, 0x00AA00FF);
}

void	draw_map(struct s_map *map)
{
	int x;
	int	y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while(x < map->width)
		{
			if (map->data[y * map->width + x] == 1)
				draw_rect(map->img, (t_rect){x * SPRITE_SIZE, y * SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE}, 0xFFFFFFFF);
			else
				draw_rect(map->img, (t_rect){x * SPRITE_SIZE, y * SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE}, 0x222222FF);
			++x;
		}
		++y;
	}
}

/* static double dist(double x0, double y0, double x1, double y1)
{
	return (sqrt((x1 - x0) * (x1 - x0) + (y1 - y0) * (y1 - y0)));
}

void	draw_rays(struct s_scene *scene)
{
	int		r, mx, my, mp, dof;
	double	rx, ry, ra, xo, yo;
	double	aTan,  nTan;
	double	dstH, hx, hy;
	double	dstV, vx, vy;

	dstH = 100000;
	hx = scene->player.x;
	hy = scene->player.y;
	dstV = 100000;
	vx = scene->player.x;
	vy = scene->player.y;

	ra = scene->player.phi - DEG_RAD * 30;
	if (ra < 0)
		ra += 2 * M_PI;
	else if (ra > 2 * M_PI)
		ra -= 2 * M_PI;
	r = 0;
	while (r < 60)
	{
		// Horizontal lines
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
		if (fabs(ra) < 0.0001 || (ra >= M_PI - 0.0001 && ra <= M_PI + 0.0001))
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
			if (mp > 0 && mp < scene->map.width * scene->map.height && scene->map.data[mp] == 1)
			{
				hx = rx;
				hy = ry;
				dstH = dist(scene->player.x, scene->player.y, hx, hy);
				break ;
			}
			rx += xo;
			ry += yo;
			++dof;
		}
		
		// vertical lines
		dof = 0;
		nTan = -tan(ra);
		if (ra > M_PI_2 && ra < 3 * M_PI_2)
		{
			rx = (((int)scene->player.x>>5)<<5) - 0.0001;
			ry = (scene->player.x - rx) * nTan + scene->player.y;
			xo = -32;
			yo = -xo * nTan;
		}
		else if (ra < M_PI_2 || ra > 3 * M_PI_2)
		{
			rx = (((int)scene->player.x>>5)<<5) + 32;
			ry = (scene->player.x - rx) * nTan + scene->player.y;
			xo = 32;
			yo = -xo * nTan;
		}
		if (fabs(ra) < 0.0001 || (ra >= M_PI - 0.0001 && ra <= M_PI + 0.0001))
		{
			ry = scene->player.y;
			rx = scene->player.x;
			dof = 16;
		}
		while (dof < 16)
		{
			mx = (int)(rx)>>5;
			my = (int)(ry)>>5;
			mp = my * scene->map.width + mx;
			if (mp > 0 && mp < scene->map.width * scene->map.height && scene->map.data[mp] == 1)
			{
				vx = rx;
				vy = ry;
				dstV = dist(scene->player.x, scene->player.y, vx, vy);
				break ;
			}
			rx += xo;
			ry += yo;
			++dof;
		}
		if (dstV < dstH)
		{
			rx = vx;
			ry = vy;
		}
		else
		{
			rx = hx;
			ry = hy;
		}
		draw_line(scene->screen, scene->player.x, scene->player.y, rx, ry, 0xFF0000FF);
		ra += DEG_RAD;
		if (ra < 0)
			ra += 2 * M_PI;
		else if (ra > 2 * M_PI)
			ra -= 2 * M_PI;
		++r;
	}
} */

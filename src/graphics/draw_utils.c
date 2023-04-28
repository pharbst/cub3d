/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlohmann <jlohmann@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 15:39:14 by jlohmann          #+#    #+#             */
/*   Updated: 2023/04/28 20:23:29 by jlohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_fill(mlx_image_t *img, t_color color)
{
	universal_memset(img->pixels, &color.pixel, BPP, img->height * img->width);
}

void	draw_point(mlx_image_t *img, t_point p, int32_t size, t_color color)
{
	t_rect	rect;

	size = abs(size);
	if (size == 1)
		set_pixel(img, p.x, p.y, color);
	else
	{
		rect = (t_rect){p.x - size / 2, p.y - size / 2, size, size};
		draw_rect(img, rect, color);
	}
}

void	draw_line(mlx_image_t *img, t_point start, t_point end, t_color color)
{
	t_point	dist;
	t_point	sign;
	int		err;
	int		e2;

	dist = (t_point){abs(end.x - start.x), -abs(end.y - start.y)};
	err = dist.x + dist.y;
	sign = (t_point){2 * (start.x < end.x) - 1, 2 * (start.y < end.y) - 1};
	while (true)
	{
		if (start.x >= 0 && start.y >= 0
			&& start.x < (int32_t)img->width && start.y < (int32_t)img->height)
			set_pixel(img, start.x, start.y, color);
		if (start.x == end.x && start.y == end.y)
			break ;
		e2 = 2 * err;
		err += dist.x * (e2 < dist.x);
		err += dist.y * (e2 > dist.y);
		start.x += sign.x * (e2 > dist.y);
		start.y += sign.y * (e2 < dist.x);
	}
}

void	draw_border(mlx_image_t *img, t_point ul, t_point br, t_color color)
{
	draw_line(img, ul, (t_point){br.x, ul.y}, color);
	draw_line(img, ul, (t_point){ul.x, br.y}, color);
	draw_line(img, (t_point){br.x, 0}, br, color);
	draw_line(img, (t_point){0, br.y}, br, color);
}

void	draw_rect(mlx_image_t *img, t_rect rect, t_color color)
{
	int32_t	x;
	int32_t	y;

	if (rect.width < 0)
	{
		rect.x -= rect.width;
		rect.width = -rect.width;
	}
	if (rect.height < 0)
	{
		rect.y -= rect.height;
		rect.height = -rect.height;
	}
	y = rect.y;
	while (y < rect.y + rect.height)
	{
		x = rect.x;
		while (x < rect.x + rect.width)
		{
			if (x >= 0 && y >= 0 && x < (int32_t)img->width && y < (int32_t)img->height)
				set_pixel(img, x, y, color);
			++x;
		}
		++y;
	}
}

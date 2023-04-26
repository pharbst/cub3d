/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlohmann <jlohmann@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 15:39:14 by jlohmann          #+#    #+#             */
/*   Updated: 2023/04/25 18:13:32 by jlohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_fill(mlx_image_t *img, t_pixel color)
{
	uint32_t	x;
	uint32_t	y;

	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			set_pixel(img, x, y, color);
			++x;
		}
		++y;
	}
}

void	draw_point(mlx_image_t *img, t_point p, int32_t size, t_pixel color)
{
	size = abs(size);
	if (size == 1)
		set_pixel(img, p.x, p.y, color);
	else
		draw_rect(img, (t_rect){p.x - size / 2, p.y - size / 2, size, size}, color);
}

void	draw_line(mlx_image_t *img, t_point start, t_point end, t_pixel color)
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
		if (start.x >= 0 && start.y >= 0 && start.x < (int32_t)img->width && start.y < (int32_t)img->height)
			set_pixel(img, start.x, start.y, color);
		if (start.x == end.x && start.y == end.y)
			break ;
		e2 = 2 * err;
		if (e2 > dist.y)
		{
			err += dist.y;
			start.x += sign.x;
		}
		if (e2 < dist.x)
		{
			err += dist.x;
			start.y += sign.y;
		}
	}
}

void	draw_triangle(mlx_image_t *img, t_point a, t_point b, t_point c, t_pixel color)
{
	draw_line(img, a, b, color);
	draw_line(img, b, c, color);
	draw_line(img, c, a, color);
}

void draw_border(mlx_image_t *img, t_point up_left, t_point bottom_right, t_pixel color)
{
	draw_line(img, up_left, (t_point){bottom_right.x, up_left.y}, color);
	draw_line(img, up_left, (t_point){up_left.x, bottom_right.y}, color);
	draw_line(img, (t_point){bottom_right.x, 0}, bottom_right, color);
	draw_line(img, (t_point){0, bottom_right.y}, bottom_right, color);
}

void	draw_rect(mlx_image_t *img, t_rect rect, t_pixel color)
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

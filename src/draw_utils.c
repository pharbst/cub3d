/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlohmann <jlohmann@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 15:39:14 by jlohmann          #+#    #+#             */
/*   Updated: 2023/03/29 14:15:57 by jlohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_point(mlx_image_t *img, int32_t x0, int32_t y0, int32_t size, uint32_t color)
{
	int32_t	x;
	int32_t	y;

	if (size == 1)
	{
		mlx_put_pixel(img, x0, y0, color);
		return ;
	}
	x = x0 - size / 2;
	y = y0 - size / 2;
	while (y < y0 + size / 2)
	{
		x = x0 - size / 2;
		while (x < x0 + size / 2)
		{
			if ((x >= 0 && y >= 0) && (x < (int32_t)img->width && y < (int32_t)img->height))
			mlx_put_pixel(img, x, y, color);
			++x;
		}
		++y;
	}
}

void	draw_line(mlx_image_t *img, int32_t x0, int32_t y0, int32_t x1, int32_t y1, uint32_t color)
{
	int dx, dy, sx, sy, err, e2;

	dx = abs(x1 - x0);
    dy = -abs(y1 - y0);
	sx = 2 * (x0 < x1) - 1;
	sy = 2 * (y0 < y1) - 1;
    err = dx + dy;
    while (true) {
		if (x0 < 0 || x0 >= (int32_t)img->width || y0 < 0 || y0 >= (int32_t)img->height)
			break ;
		mlx_put_pixel(img, x0, y0, color);
        if (x0 == x1 && y0 == y1)
			break	;
        e2 = 2 * err;
        if (e2 > dy)
		{
			err += dy;
			x0 += sx;
		}
        if (e2 < dx)
		{
			err += dx;
			y0 += sy;
		}
    }
}

void	draw_rect(mlx_image_t *img, uint32_t x0, uint32_t y0, uint32_t width, uint32_t height, uint32_t color)
{
	uint32_t	x;
	uint32_t	y;

	y = y0;
	while (y < y0 + height)
	{
		x = x0;
		while (x < x0 + width)
		{
			if (x < img->width && y < img->height)
				mlx_put_pixel(img, x, y, color);
			++x;
		}
		++y;
	}
}

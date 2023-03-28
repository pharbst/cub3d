/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlohmann <jlohmann@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 15:39:14 by jlohmann          #+#    #+#             */
/*   Updated: 2023/03/28 17:55:43 by jlohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_point(mlx_image_t *img, int32_t x0, int32_t y0, int32_t size, uint32_t color)
{
	int32_t	x;
	int32_t	y;

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

void	draw_line(mlx_image_t *img, uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, uint32_t color)
{
	int x, y, i, dx, dy, p;

	dx = x1 - x0;
	dy = y1 - y0;
	p = 2 * dy - dx;
	x = x0;
	y = x0;
	i = 0;
	while (i <= dx)
	{
		mlx_put_pixel(img, x, y, color);
		if (p < 0)
		{
			++x;
			p += 2 * dy;
		}
		else
		{
			++x;
			++y;
			p += 2 * dy - 2 * dx;
		}
		++i;
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

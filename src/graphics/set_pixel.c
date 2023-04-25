/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlohmann <jlohmann@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 14:58:20 by pharbst           #+#    #+#             */
/*   Updated: 2023/04/25 16:28:32 by jlohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_pixel	get_pixel(mlx_texture_t *tex, uint32_t x, uint32_t y)
{
	t_pixel	color;
	uint8_t	*pix;

	pix = tex->pixels + (y * tex->width + x) * tex->bytes_per_pixel; 
	color.r = pix[0];
	color.g = pix[1];
	color.b = pix[2];
	color.a = pix[3];
	return (color);
}

void	set_pixel(mlx_image_t *img, uint32_t x, uint32_t y, uint32_t color)
{
	t_pixel	*pixel_data;

	pixel_data = (t_pixel *)img->pixels;
	pixel_data[x + y * img->width].pixel = color;
}

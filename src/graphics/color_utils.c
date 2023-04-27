/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlohmann <jlohmann@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 15:42:13 by jlohmann          #+#    #+#             */
/*   Updated: 2023/04/27 21:44:42 by jlohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_color	get_pixel(mlx_texture_t *tex, uint32_t x, uint32_t y)
{
	t_color	color;
	uint8_t	*pix;

	pix = tex->pixels + (y * tex->width + x) * tex->bytes_per_pixel;
	color.r = pix[0];
	color.g = pix[1];
	color.b = pix[2];
	color.a = pix[3];
	return (color);
}

void	set_pixel(mlx_image_t *img, uint32_t x, uint32_t y, t_color color)
{
	t_color	*pixel_data;

	pixel_data = (t_color *)img->pixels;
	pixel_data[x + y * img->width].pixel = color.pixel;
}

t_color	color_dim(t_color color, double factor)
{
	t_color	new_color;

	if (factor > 1)
		factor = 1;
	else if (factor < 0)
		factor = 0;
	new_color.r = color.r * factor;
	new_color.g = color.g * factor;
	new_color.b = color.b * factor;
	new_color.a = 0xFF;
	return (new_color);
}

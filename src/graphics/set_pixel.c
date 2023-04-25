/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 14:58:20 by pharbst           #+#    #+#             */
/*   Updated: 2023/04/21 23:50:40 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_pixel(mlx_image_t *img, unsigned int x, unsigned int y,
				unsigned int color)
{
	t_pixel	*pixel_data;

	pixel_data = (t_pixel *)img->pixels;
	pixel_data[x + y * img->width].pixel = color;
}

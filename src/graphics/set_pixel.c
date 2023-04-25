/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlohmann <jlohmann@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 14:58:20 by pharbst           #+#    #+#             */
/*   Updated: 2023/04/25 15:53:19 by jlohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_pixel(mlx_image_t *img, uint32_t x, uint32_t y, uint32_t color)
{
	t_pixel	*pixel_data;

	pixel_data = (t_pixel *)img->pixels;
	pixel_data[x + y * img->width].pixel = color;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlohmann <jlohmann@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 15:22:55 by jlohmann          #+#    #+#             */
/*   Updated: 2023/04/25 16:10:09 by jlohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H

# include "MLX42/MLX42.h"
# include "cub3d_structs.h"

// color_utils.c
t_pixel	color_change_lightness(t_pixel color, double lightness);

// draw_utils.c
void	draw_fill(mlx_image_t *img, uint32_t color);
void	draw_point(mlx_image_t *img, t_point p, int32_t size, uint32_t color);
void	draw_line(mlx_image_t *img, t_point start, t_point end, uint32_t color);
void	draw_triangle(mlx_image_t *img, t_point a, t_point b, t_point c, uint32_t color);
void	draw_border(mlx_image_t *img, t_point up_left, t_point bottom_right, uint32_t color);
void	draw_rect(mlx_image_t *img, t_rect rect, uint32_t color);

#endif

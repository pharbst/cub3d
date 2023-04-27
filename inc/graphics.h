/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlohmann <jlohmann@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 15:22:55 by jlohmann          #+#    #+#             */
/*   Updated: 2023/04/27 21:45:20 by jlohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H

# include "MLX42/MLX42.h"
# include "cub3d_structs.h"

// color_utils.c
t_color	get_pixel(mlx_texture_t *tex, uint32_t x, uint32_t y);
void	set_pixel(mlx_image_t *img, uint32_t x, uint32_t y, t_color color);
t_color	color_dim(t_color color, double factor);

// draw_utils.c
void	draw_fill(mlx_image_t *img, t_color color);
void	draw_point(mlx_image_t *img, t_point p, int32_t size, t_color color);
void	draw_line(mlx_image_t *img, t_point start, t_point end, t_color color);
void	draw_border(mlx_image_t *img, t_point ul, t_point br, t_color color);
void	draw_rect(mlx_image_t *img, t_rect rect, t_color color);

#endif

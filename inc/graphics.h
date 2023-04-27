/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlohmann <jlohmann@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 15:22:55 by jlohmann          #+#    #+#             */
/*   Updated: 2023/04/27 20:49:19 by jlohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H

# include "MLX42/MLX42.h"
# include "cub3d_structs.h"

// color_utils.c
t_pixel	color_dim(t_pixel color, double factor);

// draw_utils.c
void	draw_fill(mlx_image_t *img, t_pixel color);
void	draw_point(mlx_image_t *img, t_point p, int32_t size, t_pixel color);
void	draw_line(mlx_image_t *img, t_point start, t_point end, t_pixel color);
void	draw_border(mlx_image_t *img, t_point ul, t_point br, t_pixel color);
void	draw_rect(mlx_image_t *img, t_rect rect, t_pixel color);

#endif

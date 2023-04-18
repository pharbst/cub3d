/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlohmann <jlohmann@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 15:22:55 by jlohmann          #+#    #+#             */
/*   Updated: 2023/04/18 20:02:20 by jlohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H

# include "MLX42/MLX42.h"

typedef struct s_point {
	int32_t	x;
	int32_t	y;
}	t_point;

typedef struct s_vec {
	double	x;
	double	y;
}	t_vec;

typedef struct s_rect {
	int32_t	x;
	int32_t	y;
	int32_t	width;
	int32_t	height;
}	t_rect;

typedef enum e_colors {
	WHITE = 0xAAAAAAFF,
	RED = 0xAA0000FF,
	GREEN = 0x00AA00FF,
	BLUE = 0x0000AAFF,
	YELLOW = 0xAAAA00FF,
	CYAN = 0x00AAAAFF,
	MAGENTA = 0xAA00AAFF,
	BLACK = 0x000000FF
}	t_colors;

// color_utils.c
uint32_t	get_color(char map_code);
uint32_t	color_change_lightness(uint32_t color, double lightness);

// draw_utils.c
void		draw_fill(mlx_image_t *img, uint32_t color);
void		draw_point(mlx_image_t *img, t_point p, int32_t size, uint32_t color);
void		draw_line(mlx_image_t *img, t_point start, t_point end, uint32_t color);
void		draw_triangle(mlx_image_t *img, t_point a, t_point b, t_point c, uint32_t color);
void 		draw_border(mlx_image_t *img, t_point up_left, t_point bottom_right, uint32_t color);
void		draw_rect(mlx_image_t *img, t_rect rect, uint32_t color);

#endif

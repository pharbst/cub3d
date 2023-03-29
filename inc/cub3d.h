/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlohmann <jlohmann@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 11:33:48 by jlohmann          #+#    #+#             */
/*   Updated: 2023/03/29 13:30:15 by jlohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <math.h>
# include "MLX42/MLX42.h"

# define SCREEN_WIDTH 1024
# define SCREEN_HEIGHT 512
# define SPRITE_SIZE 32

struct s_player {
	uint32_t	x;
	uint32_t	y;
	double		dx;
	double		dy;
	double		phi;
	mlx_image_t	*image_2d;
};

struct s_map {
	uint16_t	width;
	uint16_t	height;
	char		*data;
};

struct s_sprites {
	mlx_image_t	*tile_white;
	mlx_image_t	*tile_black;
};

struct s_scene {
	mlx_t				*mlx;
	mlx_image_t			*screen;
	struct s_sprites	sprites;
	struct s_map		map;
	struct s_player		player;
};

// init.c
void	scene_init(struct s_scene *scene);
// draw.c
void	img_fill_color(mlx_image_t *img, uint32_t color);
void	draw_player(struct s_player *player);
void	draw_map(struct s_scene *scene);
void	draw_rays(struct s_scene *scene);
// draw_utils.c
void	draw_point(mlx_image_t *img, int32_t x, int32_t y, int32_t size, uint32_t color);
void	draw_line(mlx_image_t *img, int32_t x0, int32_t y0, int32_t x1, int32_t y1, uint32_t color);
void    draw_rect(mlx_image_t *img, uint32_t x, uint32_t y, uint32_t width, uint32_t height, uint32_t color);
// hook.c
void	input_hook(void *param);

#endif

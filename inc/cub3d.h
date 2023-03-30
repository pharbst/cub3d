/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlohmann <jlohmann@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 11:33:48 by jlohmann          #+#    #+#             */
/*   Updated: 2023/03/30 15:50:01 by jlohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <math.h>
# include "graphics.h"

# define SCREEN_WIDTH 1024
# define SCREEN_HEIGHT 512
# define SPRITE_SIZE 32

# define DEG_RAD 0.01745329

struct s_player {
	t_point		pos;
	t_vec		dir;
	double		phi;
	mlx_image_t	*image_2d;
};

struct s_map {
	uint16_t	width;
	uint16_t	height;
	char		*data;
};

struct s_scene {
	mlx_t				*mlx;
	mlx_image_t			*screen;
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
// hook.c
void	input_hook(void *param);

#endif

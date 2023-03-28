/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlohmann <jlohmann@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 11:33:48 by jlohmann          #+#    #+#             */
/*   Updated: 2023/03/28 12:22:28 by jlohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include "MLX42/MLX42.h"

# define SCREEN_WIDTH 1024
# define SCREEN_HEIGHT 512
# define CUBE_SIZE 64;

struct s_player {
	uint32_t	x;
	uint32_t	y;
	mlx_image_t	*image_2d;
};

struct s_scene {
	mlx_t			*mlx;
	mlx_image_t		*screen;
	char			*map;
	struct s_player	player;
};

// init.c
void	scene_init(struct s_scene *scene);
// draw.c
void	img_fill_color(mlx_image_t *img, uint32_t color);
// hook.c
void	input_hook(void *param);

#endif

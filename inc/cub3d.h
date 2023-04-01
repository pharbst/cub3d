/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlohmann <jlohmann@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 11:33:48 by jlohmann          #+#    #+#             */
/*   Updated: 2023/04/01 16:40:41 by jlohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <stdio.h>
# include "libft.h"
# include "graphics.h"

# define SCREEN_WIDTH 1000
# define SCREEN_HEIGHT 500
# define FOV 0.66
# define MAP_WIDTH 400
# define MAP_HEIGHT 400
# define ROT_SPEED 0.1

# define DEG_RAD 0.01745329

typedef struct s_player {
	t_vec		pos;
	t_vec		dir;
	t_vec		plane;
	mlx_image_t	*img;
}	t_player;

typedef struct s_map {
	uint16_t	width;
	uint16_t	height;
	char		*data;
	mlx_image_t	*img;
}	t_map;

typedef struct s_scene {
	mlx_t		*mlx;
	mlx_image_t	*screen;
	t_map		map;
	t_player	player;
}	t_scene;

// init_utils.c
void		mlx_panic(void);
mlx_image_t	*init_image(mlx_t *mlx, int32_t x, int32_t y, uint32_t width, uint32_t height);
void		scene_init(t_scene *scene);
// map.c
void		map_init(mlx_t *mlx, t_map *map, char *file_path);
void		map_draw(t_map *map);
void		map_destroy(mlx_t *mlx, t_map *map);
// player.c
void		player_init(mlx_t *mlx, t_player *player, t_vec pos, t_vec dir);
void		player_update(mlx_t *mlx, t_player *player);
void		player_draw(t_player *player);
void		player_destroy(mlx_t *mlx, t_player *player);
// hooks.c
void		update(void *param);
// common_utils.c
t_vec		vec_rotate(t_vec vec, double angle);

#endif

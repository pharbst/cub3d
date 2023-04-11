/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlohmann <jlohmann@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 11:33:48 by jlohmann          #+#    #+#             */
/*   Updated: 2023/04/11 22:44:49 by jlohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <stdio.h>
# include <fcntl.h>
# include "libft.h"
# include "graphics.h"

# define SCREEN_WIDTH 1920
# define SCREEN_HEIGHT 1080
# define FOV 0.66
# define MAP_WIDTH 300
# define MAP_HEIGHT 300
# define MOVE_SPEED 0.05
# define ROT_SPEED 0.04
# define MOUSE_SENSITIVITY 0.002

typedef struct s_keystate {
	bool	W;
	bool	A;
	bool	S;
	bool	D;
	bool	LEFT;
	bool	RIGHT;
	bool	SHIFT;
}	t_keystate;

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
	mlx_image_t	*background;
	mlx_image_t	*screen;
	t_map		map;
	t_player	player;
}	t_scene;

// init_utils.c
mlx_image_t	*init_image(mlx_t *mlx, int32_t x, int32_t y, uint32_t width, uint32_t height);
// scene.c
void		scene_init(t_scene *scene);
void		scene_draw(t_scene *scene);
void		scene_destroy(t_scene *scene);
// map.c
void		map_init(mlx_t *mlx, t_map *map, char *file_path);
void		map_draw(t_map *map);
void		map_destroy(mlx_t *mlx, t_map *map);
// player.c
void		player_init(mlx_t *mlx, t_player *player, t_vec pos, t_vec dir);
void		player_update(mlx_t *mlx, t_player *player, t_map *map);
void		player_draw(t_player *player, t_map *map);
void		player_destroy(mlx_t *mlx, t_player *player);
// player_utils.c
void		player_move(t_keystate *state, t_player *player, t_map *map);
void		player_rotate(t_keystate *state, t_player *player);
// hooks.c
void		key_hook(mlx_key_data_t keydata, void* param);
void		cursor_hook(double xpos, double ypos, void* param);
void		update(void *param);
// input.c
t_keystate	input_get_keys(mlx_t *mlx);
// raycaster.c
void		raycast(t_scene *scene);
// common_utils.c
t_vec		vec_add(t_vec a, t_vec b);
t_vec		vec_scale(t_vec vec, double factor);
t_vec		vec_rotate(t_vec vec, double angle);
// error_handling.c
//void		print_help(void);
void		panic(const char *msg);
void		mlx_panic(void);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 11:33:48 by jlohmann          #+#    #+#             */
/*   Updated: 2023/04/10 10:32:46 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <stdio.h>
# include <fcntl.h>
# include "libft.h"
# include "graphics.h"
# include "cub3d_error.h"
# include "get_next_line.h"

# define SCREEN_WIDTH 1000
# define SCREEN_HEIGHT 500
# define FOV 0.66
# define MAP_WIDTH 400
# define MAP_HEIGHT 400
# define MOVE_SPEED 0.05
# define ROT_SPEED 0.07

typedef struct s_player {
	t_vec		pos;
	t_vec		dir;
	t_vec		plane;
	mlx_image_t	*img;
}	t_player;

typedef struct s_map {
	uint16_t	width;
	uint16_t	height;
	int32_t		color_floor;
	int32_t		color_ceiling;
	int32_t		fd_no;
	int32_t		fd_so;
	int32_t		fd_we;
	int32_t		fd_ea;
	char		*data;
	mlx_image_t	*img;
}	t_map;

typedef struct s_scene {
	mlx_t		*mlx;
	mlx_image_t	*screen;
	t_map		map;
	t_player	player;
}	t_scene;

// parsing
char		*convert_map(char **map, t_scene *scene);
int			find_start(int start[2], t_scene *scene);
void		*create_vector(int x, int y);
int			check_map(char **map, t_scene *scene);
void		clean_pars(t_scene *scene);
int			get_cf_colors(int fd, t_scene *scene);
int			get_map(int fd, t_scene *scene);
int			get_textures(int fd, t_scene *scene);
int			parse_map(char **map);
int			pars(char *path, t_scene *scene);
char		*skip_space(char *line);

// init_utils.c
mlx_image_t	*init_image(mlx_t *mlx, int32_t x, int32_t y, uint32_t width, uint32_t height);
// scene.c
void		scene_init(t_scene *scene);
void		scene_destroy(t_scene *scene);
// map.c
void		map_init(mlx_t *mlx, t_map *map, char *file_path);
void		map_draw(t_map *map);
void		map_destroy(mlx_t *mlx, t_map *map);
// player.c
void		player_init(mlx_t *mlx, t_player *player, t_vec pos, t_vec dir);
void		player_update(mlx_t *mlx, t_player *player);
void		player_draw(t_player *player, t_map *map);
void		player_destroy(mlx_t *mlx, t_player *player);
// hooks.c
void		update(void *param);
// common_utils.c
t_vec		vec_rotate(t_vec vec, double angle);
// error_handling.c
//void		print_help(void);
void		panic(const char *msg);
void		mlx_panic(void);

#endif

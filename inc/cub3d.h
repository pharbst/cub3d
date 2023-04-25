/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlohmann <jlohmann@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 11:33:48 by jlohmann          #+#    #+#             */
/*   Updated: 2023/04/25 17:26:20 by jlohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <stdio.h>
# include <fcntl.h>
# include "libft.h"
# include "cub3d_structs.h"
# include "graphics.h"
# include "cub3d_error.h"
# include "get_next_line.h"

# define SCREEN_WIDTH 1920
# define SCREEN_HEIGHT 1080
# define FOV 0.666
# define MAP_SIZE 300
# define MOVE_SPEED 0.05
# define ROT_SPEED 0.04
# define MOUSE_SENSITIVITY 0.002

// parsing
int			tex_init(t_scene *scene);
char		*convert_map(char **map, t_scene *scene);
int			find_start(int start[2], t_scene *scene);
void		*create_vector(int x, int y);
int			check_map(char **map, t_scene *scene);
int			get_map(int fd, t_scene *scene);
int			get_textures(int fd, t_scene *scene);
int			parse_map(char **map);
int			pars(char *path, t_scene *scene);
char		*skip_space(char *line);
char		*first_word(char *line);
char		*skip_number(char *line);
char		*cub_trim(char *line);

// init_utils.c
mlx_image_t	*init_image(mlx_t *mlx, int32_t x, int32_t y, uint32_t width, uint32_t height);
// scene.c
void		scene_init(t_scene *scene);
void		scene_draw(t_scene *scene);
void		scene_destroy(t_scene *scene);
// map.c
void		map_init(mlx_t *mlx, t_map *map);
void		map_draw(t_map *map, t_player *player);
void		map_draw_player(t_map *map, t_player *player);
void		map_destroy(mlx_t *mlx, t_map *map);
// player.c
void		player_init(t_player *player);
void		player_update(mlx_t *mlx, t_player *player, t_map *map);
// player_utils.c
void		player_move(t_keystate *state, t_player *player, t_map *map);
void		player_rotate(t_keystate *state, t_player *player);
// hooks.c
void		key_hook(mlx_key_data_t keydata, void *param);
void		cursor_hook(double xpos, double ypos, void *param);
void		scroll_hook(double xdelta, double ydelta, void* param);
void		update(void *param);
// input.c
t_keystate	input_get_keys(mlx_t *mlx);
// raycaster.c
t_hit_info	ray_cast(int x, t_player *player, t_map *map);
void		draw_wall_line(t_scene *scene, int32_t x, t_hit_info hit);
void		set_pixel(mlx_image_t *img, uint32_t x, uint32_t y, uint32_t color);
t_pixel		get_pixel(mlx_texture_t *tex, uint32_t x, uint32_t y);
// common_utils.c
t_vec		vec_add(t_vec a, t_vec b);
t_vec		vec_scale(t_vec vec, double factor);
t_vec		vec_rotate(t_vec vec, double angle);
void		universal_memset(void *dst, void *src, size_t size, size_t len);
// error_handling.c
//void		print_help(void);
void		panic(const char *msg);
void		mlx_panic(void);

//debug_tools.c
void		print_map(t_scene *scene);
void		print_player(t_scene *scene);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlohmann <jlohmann@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 12:21:58 by jlohmann          #+#    #+#             */
/*   Updated: 2023/05/03 04:17:23 by jlohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_scene	*scene;

	scene = (t_scene *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(scene->mlx);
	if (keydata.key == MLX_KEY_M && keydata.action == MLX_PRESS)
		scene->map.img->enabled = !scene->map.img->enabled;
}

void	cursor_hook(double xpos, double ypos, void *param)
{
	static bool	first = true;
	double		rot_angle;
	t_scene		*scene;

	scene = (t_scene *)param;
	if (first)
	{
		mlx_set_mouse_pos(scene->mlx, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
		first = false;
		return ;
	}
	rot_angle = MOUSE_SENSTVTY * (xpos - SCREEN_WIDTH / 2) * scene->player.fov;
	scene->player.dir = vec_rotate(scene->player.dir, rot_angle);
	scene->player.plane = vec_rotate(scene->player.plane, rot_angle);
	scene->screen->instances[0].y -= (ypos - SCREEN_HEIGHT / 2);
	if (scene->screen->instances[0].y < -SCREEN_HEIGHT / 2)
		scene->screen->instances[0].y = -SCREEN_HEIGHT / 2;
	else if (scene->screen->instances[0].y > 0)
		scene->screen->instances[0].y = 0;
	scene->background->instances[0].y = scene->screen->instances[0].y;
	mlx_set_mouse_pos(scene->mlx, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
}

void	scroll_hook(double xdelta, double ydelta, void *param)
{
	t_player	*player;

	(void)!xdelta;
	player = (t_player *)param;
	player->fov -= 0.01 * ydelta;
	if (player->fov < 0.1)
		player->fov = 0.1;
	if (player->fov > 1.2)
		player->fov = 1.2;
	player->plane = vec_scale(vec_rotate(player->dir, M_PI_2), player->fov);
}

static t_keys	get_input(mlx_t *mlx)
{
	t_keys	keys;

	keys.w = mlx_is_key_down(mlx, MLX_KEY_W);
	keys.a = mlx_is_key_down(mlx, MLX_KEY_A);
	keys.s = mlx_is_key_down(mlx, MLX_KEY_S);
	keys.d = mlx_is_key_down(mlx, MLX_KEY_D);
	keys.left = mlx_is_key_down(mlx, MLX_KEY_LEFT);
	keys.right = mlx_is_key_down(mlx, MLX_KEY_RIGHT);
	keys.shift = mlx_is_key_down(mlx, MLX_KEY_LEFT_SHIFT);
	keys.alt = mlx_is_key_down(mlx, MLX_KEY_LEFT_ALT);
	return (keys);
}

void	update(void *param)
{
	t_scene			*scene;
	t_keys			keys;

	scene = (t_scene *)param;
	keys = get_input(scene->mlx);
	player_update(&scene->player, &scene->map, keys);
	scene_draw(scene);
	map_draw(&scene->map, &scene->player);
	fps_draw(scene->fps_img, scene->mlx->delta_time);
}

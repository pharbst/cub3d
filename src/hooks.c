/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 12:21:58 by jlohmann          #+#    #+#             */
/*   Updated: 2023/04/26 21:03:23 by pharbst          ###   ########.fr       */
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
	{
		scene->map.img->enabled = !scene->map.img->enabled;
		scene->player.img->enabled = !scene->player.img->enabled;
	}
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
	rot_angle = MOUSE_SENSITIVITY * (xpos - SCREEN_WIDTH / 2) * scene->player.fov;
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

void	scroll_hook(double xdelta, double ydelta, void* param)
{
	t_player	*player;

	(void)!xdelta;
	player = (t_player *)param;
	player->fov -= 0.01 * ydelta;
	if (player->fov < 0.1)
		player->fov = 0.1;
	if (player->fov > 1.2)
		player->fov = 1.2;
	player->plane = vec_rotate((t_vec){player->dir.x * player->fov, player->dir.y * player->fov}, M_PI_2);
}

void	update(void *param)
{
	t_scene		*scene;

	scene = (t_scene *)param;
	player_update(scene->mlx, &scene->player, &scene->map);
	scene_draw(scene);
	cub_fps(scene);
	map_draw(&scene->map, &scene->player);
}

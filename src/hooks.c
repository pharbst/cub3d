/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlohmann <jlohmann@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 12:21:58 by jlohmann          #+#    #+#             */
/*   Updated: 2023/04/11 22:37:04 by jlohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	key_hook(mlx_key_data_t keydata, void* param)
{
	t_scene *scene;

	scene = (t_scene *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(scene->mlx);
	if (keydata.key == MLX_KEY_M && keydata.action == MLX_PRESS)
	{
		scene->map.img->enabled = !scene->map.img->enabled;
		scene->player.img->enabled = !scene->player.img->enabled;
	}
}

void	cursor_hook(double xpos, double ypos, void* param)
{
	double			rot_angle;
	t_scene			*scene;

	(void)!ypos;
	scene = (t_scene *)param;
	rot_angle = MOUSE_SENSITIVITY * (xpos - SCREEN_WIDTH / 2);
	scene->player.dir = vec_rotate(scene->player.dir, rot_angle);
	scene->player.plane = vec_rotate(scene->player.plane, rot_angle);
	mlx_set_mouse_pos(scene->mlx, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
}

void	update(void *param)
{
	t_scene		*scene;

	scene = (t_scene *)param;
	player_update(scene->mlx, &scene->player, &scene->map);
	scene_draw(scene);
	player_draw(&scene->player, &scene->map);
}

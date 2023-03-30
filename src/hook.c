/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlohmann <jlohmann@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 12:21:58 by jlohmann          #+#    #+#             */
/*   Updated: 2023/03/30 19:32:23 by jlohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void input_hook(void *param)
{
	struct s_scene *scene;
	struct s_player *player;
	bool change;

	scene = (struct s_scene *)param;
	player = &scene->player;
	change = false;
	if (mlx_is_key_down(scene->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(scene->mlx);
	if (mlx_is_key_down(scene->mlx, MLX_KEY_UP))
	{
		change = true;
		player->pos.x += round(player->dir.x);
		player->pos.y += round(player->dir.y);
	}
	else if (mlx_is_key_down(scene->mlx, MLX_KEY_DOWN))
	{
		change = true;
		player->pos.x -= round(player->dir.x);
		player->pos.y -= round(player->dir.y);
	}
	// speed is not consistent
	if (mlx_is_key_down(scene->mlx, MLX_KEY_RIGHT))
	{
		change = true;
		player->phi += 0.1 - (2 * M_PI * (player->phi + 0.1 > 2 * M_PI));
		player->dir.x = cos(player->phi) * 5;
		player->dir.y = sin(player->phi) * 5;
	}
	else if (mlx_is_key_down(scene->mlx, MLX_KEY_LEFT))
	{
		change = true;
		scene->player.phi -= 0.1 - (2 * M_PI * (scene->player.phi - 0.1 < 0));
		player->dir.x = cos(player->phi) * 5;
		player->dir.y = sin(player->phi) * 5;
	}
	if (change)
	{
		draw_map(&scene->map);
		draw_player(player);
		//draw_rays(scene);
	}
}

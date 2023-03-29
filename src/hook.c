/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlohmann <jlohmann@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 12:21:58 by jlohmann          #+#    #+#             */
/*   Updated: 2023/03/29 16:06:35 by jlohmann         ###   ########.fr       */
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
		player->x += round(player->dx);
		player->y += round(player->dy);
	}
	else if (mlx_is_key_down(scene->mlx, MLX_KEY_DOWN))
	{
		change = true;
		player->x -= round(player->dx);
		player->y -= round(player->dy);
	}
	// speed is not consistent
	if (mlx_is_key_down(scene->mlx, MLX_KEY_RIGHT))
	{
		change = true;
		player->phi += 0.1 - (2 * M_PI * (player->phi + 0.1 > 2 * M_PI));
		player->dx = cos(player->phi) * 2;
		player->dy = sin(player->phi) * 2;
	}
	else if (mlx_is_key_down(scene->mlx, MLX_KEY_LEFT))
	{
		change = true;
		scene->player.phi -= 0.1 - (2 * M_PI * (scene->player.phi - 0.1 < 0));
		player->dx = cos(player->phi) * 2;
		player->dy = sin(player->phi) * 2;
	}
	if (change)
	{
		draw_map(scene);
		draw_player(player);
		draw_rays(scene);
	}
}

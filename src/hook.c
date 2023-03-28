/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlohmann <jlohmann@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 12:21:58 by jlohmann          #+#    #+#             */
/*   Updated: 2023/03/28 18:01:40 by jlohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	input_hook(void *param)
{
	struct s_scene	*scene;
	struct s_player	*player;

	scene = (struct s_scene *)param;
	player = &scene->player;
	if (mlx_is_key_down(scene->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(scene->mlx);
	if (mlx_is_key_down(scene->mlx, MLX_KEY_UP))
	{
		player->x += player->dx;
		player->y += player->dy;
	}
	else if (mlx_is_key_down(scene->mlx, MLX_KEY_DOWN))
	{
		player->x -= player->dx;
		player->y -= player->dy;
	}
	// speed is not consistent
	if (mlx_is_key_down(scene->mlx, MLX_KEY_RIGHT))
	{
		player->phi += 0.1 + (2 * M_PI * (player->phi > 2*M_PI));
		player->dx = cos(player->phi) * 5;
		player->dy = sin(player->phi) * 5;
	}
	else if (mlx_is_key_down(scene->mlx, MLX_KEY_LEFT))
	{
		scene->player.phi -= 0.1 + (2 * M_PI * (scene->player.phi < 0));
		player->dx = cos(player->phi) * 5;
		player->dy = sin(player->phi) * 5;
	}
	draw_player(player);
}

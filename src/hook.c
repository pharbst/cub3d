/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlohmann <jlohmann@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 12:21:58 by jlohmann          #+#    #+#             */
/*   Updated: 2023/03/28 12:22:15 by jlohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	input_hook(void *param)
{
	struct s_scene	*scene;

	scene = (struct s_scene *)param;
	if (mlx_is_key_down(scene->mlx, MLX_KEY_UP))
		scene->player.y -= 5;
	if (mlx_is_key_down(scene->mlx, MLX_KEY_RIGHT))
		scene->player.x += 5;
	if (mlx_is_key_down(scene->mlx, MLX_KEY_DOWN))
		scene->player.y += 5;
	if (mlx_is_key_down(scene->mlx, MLX_KEY_LEFT))
		scene->player.x -= 5;
	scene->player.image_2d->instances[0].x = scene->player.x;
	scene->player.image_2d->instances[0].y = scene->player.y;
}

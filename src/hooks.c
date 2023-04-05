/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlohmann <jlohmann@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 12:21:58 by jlohmann          #+#    #+#             */
/*   Updated: 2023/04/05 11:41:00 by jlohmann         ###   ########.fr       */
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

void	update(void *param)
{
	t_scene		*scene;

	scene = (t_scene *)param;
	player_update(scene->mlx, &scene->player);
	player_draw(&scene->player, &scene->map);
	draw_fill(scene->screen, 0x000000FF);
	raycast(&scene->player, &scene->map, scene);
}

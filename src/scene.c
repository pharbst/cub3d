/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlohmann <jlohmann@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 13:06:21 by jlohmann          #+#    #+#             */
/*   Updated: 2023/04/01 21:13:59 by jlohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	scene_init(t_scene *scene)
{
	scene->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "cub3D", true);
	if (scene->mlx == NULL)
		mlx_panic();
	scene->screen = init_image(scene->mlx, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	draw_fill(scene->screen, 0x000000FF);
	map_init(scene->mlx, &scene->map, NULL);
	player_init(scene->mlx, &scene->player, (t_vec){8.0, 8.0}, (t_vec){0.0, 1.0});
}

void	scene_destroy(t_scene *scene)
{
	player_destroy(scene->mlx, &scene->player);
	map_destroy(scene->mlx, &scene->map);
	mlx_delete_image(scene->mlx, scene->screen);
	mlx_terminate(scene->mlx);
}

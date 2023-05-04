/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlohmann <jlohmann@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 11:36:56 by jlohmann          #+#    #+#             */
/*   Updated: 2023/05/04 16:54:22 by jlohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_error.h"

int32_t	main(int argc, char **argv)
{
	t_scene	scene;

	if (argc != 2)
		return (cub_errno(WRITE, ERARG), cub_strerror(), EXIT_FAILURE);
	if (pars(argv[1], &scene))
		return (cub_strerror(), scene_destroy(&scene, -1), EXIT_FAILURE);
	if (!scene_init(&scene))
	{
		free(scene.map.data);
		return (EXIT_FAILURE);
	}
	mlx_loop_hook(scene.mlx, update, &scene);
	mlx_key_hook(scene.mlx, key_hook, &scene);
	mlx_cursor_hook(scene.mlx, cursor_hook, &scene);
	mlx_scroll_hook(scene.mlx, scroll_hook, &scene.player);
	mlx_loop(scene.mlx);
	map_destroy(scene.mlx, &scene.map);
	scene_destroy(&scene, 3);
	return (EXIT_SUCCESS);
}

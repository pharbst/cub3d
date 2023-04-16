/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 11:36:56 by jlohmann          #+#    #+#             */
/*   Updated: 2023/04/16 02:55:00 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_error.h"

void	debug_print(t_scene *scene)
{
	printf("player pos: %f, %f| dir: %f, %f| plane: %f, %f", scene->player.pos.x, scene->player.pos.y, scene->player.dir.x, scene->player.dir.y, scene->player.plane.x, scene->player.plane.y);
}

int32_t	main(int argc, char **argv)
{
	t_scene	scene;

	if (argc != 2)
		return (cub_errno(WRITE, ERARG), cub_strerror(), EXIT_FAILURE);
	if (pars(argv[1], &scene))
		return (cub_strerror(), EXIT_FAILURE);
	debug_print(&scene);
	scene_init(&scene);
	mlx_loop_hook(scene.mlx, update, &scene);
	mlx_key_hook(scene.mlx, key_hook, &scene);
	mlx_cursor_hook(scene.mlx, cursor_hook, &scene);
	mlx_loop(scene.mlx);
	scene_destroy(&scene);
	return (EXIT_SUCCESS);
}

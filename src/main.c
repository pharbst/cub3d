/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 11:36:56 by jlohmann          #+#    #+#             */
/*   Updated: 2023/04/04 16:19:20 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int32_t	main(int argc, char **argv)
{
	t_scene	scene;

	if (argc != 2 || pars(argv[1], &scene))
		return (EXIT_FAILURE);
	scene_init(&scene);
	mlx_loop_hook(scene.mlx, update, &scene);
	mlx_loop(scene.mlx);
	scene_destroy(&scene);
	return (EXIT_SUCCESS);
}

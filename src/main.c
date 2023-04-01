/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlohmann <jlohmann@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 11:36:56 by jlohmann          #+#    #+#             */
/*   Updated: 2023/04/01 21:14:36 by jlohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int32_t	main(void)
{
	t_scene	scene;

	scene_init(&scene);
	mlx_loop_hook(scene.mlx, update, &scene);
	mlx_loop(scene.mlx);
	scene_destroy(&scene);
	return (EXIT_SUCCESS);
}

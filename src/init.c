/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlohmann <jlohmann@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 12:20:31 by jlohmann          #+#    #+#             */
/*   Updated: 2023/03/28 12:24:50 by jlohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	mlx_panic(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

void	scene_init(struct s_scene *scene)
{
	scene->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "cub3d", true);
	if (scene->mlx == NULL)
		mlx_panic();
	scene->screen = mlx_new_image(scene->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (scene->screen == NULL)
		mlx_panic();
	img_fill_color(scene->screen, 0x000000FF);
	if (mlx_image_to_window(scene->mlx, scene->screen, 0, 0) < 0)
		mlx_panic();
	// v-- TODO: set map with file parsing function
	scene->map = malloc(sizeof(char) * 8 * 8);
	if (scene->map == NULL)
		mlx_panic(); // not a mlx_error. Call another function to panic.
	scene->map = (char[64]){
		1, 1, 1, 1, 1, 1, 1, 1,
		1, 0, 0, 0, 0, 0, 1, 1,
		1, 0, 1, 0, 1, 0, 0, 1,
		1, 0, 1, 0, 1, 1, 0, 1,
		1, 0, 1, 0, 0, 0, 0, 1,
		1, 0, 1, 1, 1, 1, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 1,
		1, 1, 1, 1, 1, 1, 1, 1
	};
	scene->player = (struct s_player){300, 300, mlx_new_image(scene->mlx, 8, 8)};
	if (scene->player.image_2d == NULL)
		mlx_panic();
	img_fill_color(scene->player.image_2d, 0xFFFF00FF);
	if (mlx_image_to_window(scene->mlx, scene->player.image_2d, scene->player.x, scene->player.y) < 0)
		mlx_panic();
}

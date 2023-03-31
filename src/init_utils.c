/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlohmann <jlohmann@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 12:20:31 by jlohmann          #+#    #+#             */
/*   Updated: 2023/03/31 12:32:56 by jlohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	mlx_panic(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

mlx_image_t	*init_image(mlx_t *mlx, int32_t x, int32_t y, uint32_t width, uint32_t height)
{
	mlx_image_t	*img;

	img = mlx_new_image(mlx, width, height);
	if (img == NULL)
		mlx_panic();
	if (mlx_image_to_window(mlx, img, x, y) < 0)
	{
		mlx_delete_image(mlx, img);
		mlx_panic();
	}
	return (img);
}

void	scene_init(t_scene *scene)
{
	scene->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "cub3D", true);
	if (scene->mlx == NULL)
		mlx_panic();
	scene->screen = init_image(scene->mlx, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	draw_fill(scene->screen, 0x000000FF);
	map_init(scene->mlx, &scene->map, NULL);
	player_init(scene->mlx, &scene->player, (t_vec){220, 220}, (t_vec){0.0, 1.0});
}

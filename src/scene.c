/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 13:06:21 by jlohmann          #+#    #+#             */
/*   Updated: 2023/04/25 17:14:10 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	scene_init(t_scene *scene)
{
	scene->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "cub3D", true);
	if (scene->mlx == NULL)
		mlx_panic();
	mlx_set_cursor_mode(scene->mlx, MLX_MOUSE_HIDDEN);
	scene->background = init_image(scene->mlx, 0, -SCREEN_HEIGHT / 4, SCREEN_WIDTH, 1.5 * SCREEN_HEIGHT);
	draw_rect(scene->background, (t_rect){0, 0, SCREEN_WIDTH, 0.75 * SCREEN_HEIGHT}, scene->tex.ceiling.pixel);
	draw_rect(scene->background, (t_rect){0, 0.75 * SCREEN_HEIGHT, SCREEN_WIDTH, 1.5 * SCREEN_HEIGHT}, scene->tex.floor.pixel);
	scene->screen = init_image(scene->mlx, 0, -SCREEN_HEIGHT / 4, SCREEN_WIDTH, 1.5 * SCREEN_HEIGHT);
	scene->fps_screen = init_image(scene->mlx, SCREEN_HEIGHT - 40, SCREEN_WIDTH - 15, 40, 20);
	map_init(scene->mlx, &scene->map);
	player_init(&scene->player);
}

void	scene_draw(t_scene *scene)
{
	int			x;
	t_hit_info	hit;

	draw_fill(scene->screen, 0x00000000);
	x = 0;
	while (x < SCREEN_WIDTH)
	{
		hit = ray_cast(x, &scene->player, &scene->map);
		draw_wall_line(scene, x, hit);
		++x;
	}
}

void	scene_destroy(t_scene *scene)
{
	map_destroy(scene->mlx, &scene->map);
	mlx_delete_image(scene->mlx, scene->screen);
	mlx_delete_texture(scene->tex.t_north);
	mlx_delete_texture(scene->tex.t_west);
	mlx_delete_texture(scene->tex.t_south);
	mlx_delete_texture(scene->tex.t_east);
	mlx_terminate(scene->mlx);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlohmann <jlohmann@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 13:06:21 by jlohmann          #+#    #+#             */
/*   Updated: 2023/04/13 22:14:36 by jlohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_textures textures_load(void)
{
	t_textures	tex;

	tex.t_north = mlx_load_png("./scenes/textures/Air.png");
	tex.t_east = mlx_load_png("./scenes/textures/Earth.png");
	tex.t_south = mlx_load_png("./scenes/textures/Fire.png");
	tex.t_west = mlx_load_png("./scenes/textures/Water.png");
	tex.floor = 0x262626FF;
	tex.ceiling = 0x402DA3FF;
	return (tex);
}

void	scene_init(t_scene *scene)
{
	scene->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "cub3D", true);
	if (scene->mlx == NULL)
		mlx_panic();
	scene->textures = textures_load();
	mlx_set_cursor_mode(scene->mlx, MLX_MOUSE_HIDDEN);
	scene->background = init_image(scene->mlx, 0, -SCREEN_HEIGHT / 4, SCREEN_WIDTH, 1.5 * SCREEN_HEIGHT);
	draw_rect(scene->background, (t_rect){0, 0, SCREEN_WIDTH, 0.75 * SCREEN_HEIGHT}, scene->textures.ceiling);
	draw_rect(scene->background, (t_rect){0, 0.75 * SCREEN_HEIGHT, SCREEN_WIDTH, 1.5 * SCREEN_HEIGHT}, scene->textures.floor);
	scene->screen = init_image(scene->mlx, 0, -SCREEN_HEIGHT / 4, SCREEN_WIDTH, 1.5 * SCREEN_HEIGHT);
	map_init(scene->mlx, &scene->map, NULL);
	player_init(scene->mlx, &scene->player, (t_vec){8.0, 8.0}, (t_vec){0.0, 1.0});
}

void	scene_draw(t_scene *scene)
{
	draw_fill(scene->screen, 0x00000000);
	raycast(scene);
}

void	scene_destroy(t_scene *scene)
{
	player_destroy(scene->mlx, &scene->player);
	map_destroy(scene->mlx, &scene->map);
	mlx_delete_image(scene->mlx, scene->screen);
	mlx_terminate(scene->mlx);
}

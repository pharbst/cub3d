/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 13:06:21 by jlohmann          #+#    #+#             */
/*   Updated: 2023/04/14 02:37:59 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_tex	textures_load(void)
{
	t_tex	tex;

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
	scene->tex = textures_load();
	mlx_set_cursor_mode(scene->mlx, MLX_MOUSE_HIDDEN);
	scene->background = init_image(scene->mlx, 0, -SCREEN_HEIGHT / 4, SCREEN_WIDTH, 1.5 * SCREEN_HEIGHT);
	draw_rect(scene->background, (t_rect){0, 0, SCREEN_WIDTH, 0.75 * SCREEN_HEIGHT}, scene->tex.ceiling);
	draw_rect(scene->background, (t_rect){0, 0.75 * SCREEN_HEIGHT, SCREEN_WIDTH, 1.5 * SCREEN_HEIGHT}, scene->tex.floor);
	scene->screen = init_image(scene->mlx, 0, -SCREEN_HEIGHT / 4, SCREEN_WIDTH, 1.5 * SCREEN_HEIGHT);
	map_init(scene->mlx, &scene->map, NULL);
	player_init(scene->mlx, &scene->player, (t_vec){8.0, 8.0}, (t_vec){0.0, -1.0});
}

void	scene_draw(t_scene *scene)
{
	int				x;
	t_hit_info		hit;
	uint32_t		color;

	draw_fill(scene->screen, 0x00000000);
	x = 0;
	while (x < SCREEN_WIDTH)
	{
		hit = ray_cast(x, &scene->player, &scene->map);
		//color = get_color(scene->map.data[hit.block_pos.y * scene->map.width + hit.block_pos.x]);
		color = get_color(hit.side);
		draw_wall_line(scene->screen, x, hit.dist, color);
		++x;
	}
}

void	scene_destroy(t_scene *scene)
{
	player_destroy(scene->mlx, &scene->player);
	map_destroy(scene->mlx, &scene->map);
	mlx_delete_image(scene->mlx, scene->screen);
	mlx_terminate(scene->mlx);
}

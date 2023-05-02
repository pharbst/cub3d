/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlohmann <jlohmann@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 13:06:21 by jlohmann          #+#    #+#             */
/*   Updated: 2023/05/02 21:29:57 by jlohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_background(mlx_image_t *background, t_color ceiling, t_color floor)
{
	int		y;
	t_color	color;

	y = 0;
	while (y < 0.75 * SCREEN_HEIGHT)
	{
		color = color_dim(ceiling, 1 - (0.9 * y) / (0.75 * SCREEN_HEIGHT));
		uni_memset(
			background->pixels + (y * background->width * BPP),
			&color.pixel, BPP, background->width);
		++y;
	}
	while (y < 1.5 * SCREEN_HEIGHT)
	{
		color = color_dim(floor, y / (0.75 * SCREEN_HEIGHT) - 0.9);
		uni_memset(
			background->pixels + (y * background->width * BPP),
			&color.pixel, BPP, background->width);
		++y;
	}
}

void	scene_init(t_scene *scene)
{
	scene->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "cub3D", true);
	if (scene->mlx == NULL)
		mlx_panic();
	mlx_set_cursor_mode(scene->mlx, MLX_MOUSE_HIDDEN);
	scene->background = init_image(
			scene->mlx,
			(t_rect){0, -SCREEN_HEIGHT / 4, SCREEN_WIDTH, 1.5 * SCREEN_HEIGHT});
	draw_background(scene->background, scene->tex.ceiling, scene->tex.floor);
	scene->screen = init_image(
			scene->mlx,
			(t_rect){0, -SCREEN_HEIGHT / 4, SCREEN_WIDTH, 1.5 * SCREEN_HEIGHT});
	map_init(scene->mlx, &scene->map);
	player_init(&scene->player);
}

void	scene_draw(t_scene *scene)
{
	int			screen_x;
	double		x;
	t_vec		ray_dir;
	t_hit_info	hit;

	draw_fill(scene->screen, (t_color){0x00000000});
	screen_x = 0;
	while (screen_x < SCREEN_WIDTH)
	{
		x = 2 * screen_x / (double)SCREEN_WIDTH - 1;
		ray_dir = vec_add(scene->player.dir, vec_scale(scene->player.plane, x));
		hit = ray_cast(&scene->player, &scene->map, ray_dir);
		draw_wall_line(scene, screen_x, hit);
		++screen_x;
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

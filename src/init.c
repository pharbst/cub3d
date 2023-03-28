/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlohmann <jlohmann@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 12:20:31 by jlohmann          #+#    #+#             */
/*   Updated: 2023/03/28 17:58:39 by jlohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	mlx_panic(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

void	map_init(struct s_map *map, uint16_t width, uint16_t height, char *file_path)
{
	(void)!file_path; // TODO: use for file parsing.
	map->width = width; map->height = height;
	map->data = malloc(sizeof(char) * width * height);
	if (map->data == NULL)
		mlx_panic(); // not a mlx_error. Call another function to panic.
	map->data = memcpy(map->data, (char[256]){
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1,
		1,0,1,0,1,0,0,1,0,0,0,0,0,0,0,1,
		1,0,1,0,1,1,0,1,0,0,0,0,0,0,0,1,
		1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,1,
		1,0,1,1,1,1,0,1,1,0,1,1,1,1,1,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,1,1,1,1,1,0,0,0,0,1,1,1,1,0,1,
		1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,
		1,0,1,1,1,1,0,0,0,0,1,0,1,0,0,1,
		1,0,1,0,0,1,0,1,1,1,1,0,0,1,0,1,
		1,0,1,0,1,1,0,1,0,0,0,0,0,0,0,1,
		1,0,1,0,0,0,0,1,0,0,0,1,0,0,1,1,
		1,0,1,1,1,1,1,1,0,1,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
	}, 256);
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
	scene->sprites = (struct s_sprites){
		mlx_new_image(scene->mlx, SPRITE_SIZE, SPRITE_SIZE),
		mlx_new_image(scene->mlx, SPRITE_SIZE, SPRITE_SIZE)
	};
	if (scene->sprites.tile_white == NULL || scene->sprites.tile_black == NULL)
		mlx_panic();
	img_fill_color(scene->sprites.tile_white, 0x660088FF);
	img_fill_color(scene->sprites.tile_black, 0x000000FF);
	// v-- TODO: set map with file parsing function
	map_init(&scene->map, 16, 16, NULL); // don't change these values until file parser is implemented!
	draw_map(scene);
	scene->player = (struct s_player){300, 300, 0, 0, M_PI, mlx_new_image(scene->mlx, 16, 16)};
	if (scene->player.image_2d == NULL)
		mlx_panic();
	draw_point(scene->player.image_2d, 8, 8, 8, 0x00AA00FF);
	if (mlx_image_to_window(scene->mlx, scene->player.image_2d, scene->player.x, scene->player.y) < 0)
		mlx_panic();
	//draw_point(scene->screen, 0, 0, 20, 0xFFFF00FF);
	//draw_line(scene->screen, 0, 0, scene->player.x, scene->player.y, 0xFF0000FF);
	//draw_rect(scene->screen, 0, 255, 512, 512, 0xAA0000FF);
}

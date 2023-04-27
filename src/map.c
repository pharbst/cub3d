/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlohmann <jlohmann@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 09:34:03 by jlohmann          #+#    #+#             */
/*   Updated: 2023/04/27 20:39:51 by jlohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	map_init(mlx_t *mlx, t_map *map)
{
	map->img = init_image(mlx, (t_rect){50, 50, MAP_SIZE, MAP_SIZE});
}

void	map_draw(t_map *map, t_player *player)
{
	const int32_t	block_size = MAP_SIZE / 15;
	t_point			data_pos;
	t_point			img_pos;
	t_pixel			color;

	draw_fill(map->img, (t_pixel){0x00000000});
	data_pos.y = floor(player->pos.y - 7);
	img_pos.y = 0;
	if (data_pos.y < 0)
	{
		img_pos.y = -data_pos.y;
		data_pos.y = 0;
	}
	else if (data_pos.y + 7 > map->height)
		data_pos.y = map->height - 14;
	while (img_pos.y < 15 && data_pos.y < map->height)
	{
		data_pos.x = floor(player->pos.x - 7);
		img_pos.x = 0;
		if (data_pos.x < 0)
		{
			img_pos.x = -data_pos.x;
			data_pos.x = 0;
		}
		else if (data_pos.x + 7 > map->width)
			data_pos.x = map->width - 14;
		while (img_pos.x < 15 && data_pos.x < map->width)
		{
			if (map->data[data_pos.y * map->width + data_pos.x] == '0')
				color = (t_pixel){0xFF000000};
			else if (map->data[data_pos.y * map->width + data_pos.x] == '1')
				color = (t_pixel){0xFFAAAAAA};
			draw_rect(map->img, (t_rect){img_pos.x * block_size, img_pos.y * block_size, block_size, block_size}, color);
			++data_pos.x;
			++img_pos.x;
		}
		++data_pos.y;
		++img_pos.y;
	}
	map_draw_player(map, player);
	draw_border(map->img, (t_point){0, 0}, (t_point){MAP_SIZE - 1, MAP_SIZE - 1}, (t_pixel){0xFFFFFFFF});
}

void	map_draw_player(t_map *map, t_player *player)
{
	const t_point	offset = (t_point){
		map->img->width / 2, map->img->height / 2
	};
	const t_pixel	color = (t_pixel){0xFF00FFFF};
	t_point			left;
	t_point			right;

	left = (t_point){
		offset.x + player->dir.x * 8 + player->plane.x * 8,
		offset.y + player->dir.y * 8 + player->plane.y * 8
	};
	right = (t_point){
		offset.x + player->dir.x * 8 + -player->plane.x * 8,
		offset.y + player->dir.y * 8 + -player->plane.y * 8
	};
	draw_point(map->img, offset, 5, (t_pixel){0xFF00AA00});
	draw_line(map->img, offset, left, color);
	draw_line(map->img, left, right, color);
	draw_line(map->img, offset, right, color);
}

void	map_destroy(mlx_t *mlx, t_map *map)
{
	free(map->data);
	mlx_delete_image(mlx, map->img);
}

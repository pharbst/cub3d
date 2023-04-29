/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlohmann <jlohmann@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 09:34:03 by jlohmann          #+#    #+#             */
/*   Updated: 2023/04/29 22:17:45 by jlohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	map_init(mlx_t *mlx, t_map *map)
{
	mlx_image_t	*img;

	map->img = init_image(mlx, (t_rect){50, 50, MAP_SIZE, MAP_SIZE});
	map->pixbuf = init_map_pixbuf(map); // protect!
	img = mlx_texture_to_image(mlx, map->pixbuf);
}

void	map_draw(t_map *map, t_player *player)
{
	t_point			data_pos;
	t_point			img_pos;
	int				len;

	draw_fill(map->img, (t_color){0x00000000});
	data_pos.y = ((player->pos.y - 7) * BLOCK_SIZE) - (BLOCK_SIZE / 2);
	data_pos.x = ((player->pos.x - 7) * BLOCK_SIZE) - (BLOCK_SIZE / 2);
	img_pos = (t_point){0, 0};
	if (data_pos.y < 0)
		img_pos.y -= data_pos.y;
	if (data_pos.x < 0)
	{
		img_pos.x -= data_pos.x;
		data_pos.x = 0;
	}
	if (map->pixbuf->width < map->img->width)
		len = map->pixbuf->width * BPP;
	else if (map->pixbuf->width - data_pos.x < map->img->width)
		len = (map->pixbuf->width - img_pos.x - data_pos.x) * BPP;
	else
		len = (map->img->width - img_pos.x) * BPP;
	while (img_pos.y < (int)map->img->height)
	{
		if (img_pos.y + data_pos.y >= (int)map->pixbuf->height)
			break ;
		ft_memcpy(
			map->img->pixels + (img_pos.y * map->img->width + img_pos.x) * BPP,
			map->pixbuf->pixels + ((img_pos.y + data_pos.y) * map->pixbuf->width + data_pos.x) * BPP,
			len);
		++img_pos.y;
	}
	map_draw_player(map, player);
	draw_border(map->img, (t_point){0, 0}, (t_point){MAP_SIZE - 1, MAP_SIZE - 1}, (t_color){0xFF0000FF});
}

void	map_draw_player(t_map *map, t_player *player)
{
	const t_point	offset = (t_point){
		map->img->width / 2, map->img->height / 2
	};
	const t_color	color = (t_color){0xFF00FFFF};
	t_point			left;
	t_point			right;

	left = (t_point){
		offset.x + player->dir.x * 8 + player->plane.x * 8,
		offset.y + player->dir.y * 8 + player->plane.y * 8
	};
	right = (t_point){
		offset.x + player->dir.x * 8 - player->plane.x * 8,
		offset.y + player->dir.y * 8 - player->plane.y * 8
	};
	draw_point(map->img, offset, 5, (t_color){0xFF00AA00});
	draw_line(map->img, offset, left, color);
	draw_line(map->img, left, right, color);
	draw_line(map->img, offset, right, color);
}

void	map_destroy(mlx_t *mlx, t_map *map)
{
	free(map->data);
	mlx_delete_texture(map->pixbuf);
	mlx_delete_image(mlx, map->img);
}

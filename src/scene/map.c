/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlohmann <jlohmann@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 09:34:03 by jlohmann          #+#    #+#             */
/*   Updated: 2023/05/03 02:38:21 by jlohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	map_init(mlx_t *mlx, t_map *map)
{
	mlx_image_t	*img;

	map->img = init_image(mlx, (t_rect){50, 50, MAP_SIZE, MAP_SIZE});
	init_map_pixbuf(map);
	if (map->pixbuf == NULL)
		panic("Failed to allocate memory.");
	img = mlx_texture_to_image(mlx, map->pixbuf);
}

static void	map_draw_map(t_point img, t_point data, t_map *map)
{
	int				len;
	mlx_texture_t	*pixbuf;

	pixbuf = map->pixbuf;
	if (pixbuf->width < map->img->width)
		len = pixbuf->width * BPP;
	else if (pixbuf->width - data.x < map->img->width)
		len = (pixbuf->width - img.x - data.x) * BPP;
	else
		len = (map->img->width - img.x) * BPP;
	while (img.y < (int)map->img->height)
	{
		if (img.y + data.y >= (int)pixbuf->height)
			break ;
		ft_memcpy(
			map->img->pixels + (img.y * map->img->width + img.x) * BPP,
			pixbuf->pixels + ((img.y + data.y) * pixbuf->width + data.x) * BPP,
			len);
		++img.y;
	}
}

static void	map_draw_player(mlx_image_t *img, t_player *player)
{
	const t_point	offset = (t_point){
		img->width / 2, img->height / 2
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
	draw_point(img, offset, 5, (t_color){0xFF00AA00});
	draw_line(img, offset, left, color);
	draw_line(img, left, right, color);
	draw_line(img, offset, right, color);
}

void	map_draw(t_map *map, t_player *player)
{
	t_point	data_pos;
	t_point	img_pos;

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
	map_draw_map(img_pos, data_pos, map);
	map_draw_player(map->img, player);
	draw_border(map->img, (t_point){0, 0},
		(t_point){MAP_SIZE - 1, MAP_SIZE - 1}, (t_color){0xFF0000FF});
}

void	map_destroy(mlx_t *mlx, t_map *map)
{
	free(map->data);
	mlx_delete_texture(map->pixbuf);
	mlx_delete_image(mlx, map->img);
}

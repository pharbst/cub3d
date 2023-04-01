/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlohmann <jlohmann@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 09:34:03 by jlohmann          #+#    #+#             */
/*   Updated: 2023/04/01 16:38:11 by jlohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	map_init(mlx_t *mlx, t_map *map, char *file_path)
{
	(void)!file_path; // TODO: use for file parsing.
	map->width = 16;
	map->height = 16;
	map->data = malloc(sizeof(char) * map->width * map->height);
	if (map->data == NULL)
		mlx_panic(); // not a mlx_error. Call another function to panic.
	map->data = ft_memcpy(map->data, (char[256]){
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
	map->img = init_image(mlx, 50, 50, MAP_HEIGHT, MAP_WIDTH);
	map_draw(map);
}

void	map_draw(t_map *map)
{
	const int32_t	block_size = MAP_HEIGHT / map->height;
	int16_t			x;
	int16_t			y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while(x < map->width)
		{
			if (map->data[y * map->width + x] == 1)
				draw_rect(map->img, (t_rect){x * block_size, y * block_size, block_size, block_size}, 0xFFFFFFFF);
			else
				draw_rect(map->img, (t_rect){x * block_size, y * block_size, block_size, block_size}, 0x222222FF);
			++x;
		}
		++y;
	}
}

void	map_destroy(mlx_t *mlx, t_map *map)
{
	free(map->data);
	mlx_delete_image(mlx, map->img);	
}

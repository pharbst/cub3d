/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlohmann <jlohmann@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 12:21:07 by jlohmann          #+#    #+#             */
/*   Updated: 2023/03/28 17:57:16 by jlohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	img_fill_color(mlx_image_t *img, uint32_t color)
{
	uint32_t	x;
	uint32_t	y;

	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			mlx_put_pixel(img, x, y, color);
			++x;
		}
		++y;
	}
}

void	draw_player(struct s_player *player)
{
	player->image_2d->instances[0].x = player->x;
	player->image_2d->instances[0].y = player->y;
	//draw_line(player->image_2d, player->x, player->y, player->x + 3 * player->dx, player->y + 3 * player->dy);
}

void	draw_map(struct s_scene *scene)
{
	int x;
	int	y;

	y = 0;
	while (y < scene->map.height)
	{
		x = 0;
		while(x < scene->map.width)
		{
			if (scene->map.data[y * scene->map.width + x] == 1)
			// TODO: draw directly to screen instead of placing sprite instances
				mlx_image_to_window(scene->mlx, scene->sprites.tile_white, x * SPRITE_SIZE, y * SPRITE_SIZE);
			else
				mlx_image_to_window(scene->mlx, scene->sprites.tile_black, x * SPRITE_SIZE, y * SPRITE_SIZE);
			++x;
		}
		++y;
	}
}

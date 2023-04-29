/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlohmann <jlohmann@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 12:20:31 by jlohmann          #+#    #+#             */
/*   Updated: 2023/04/29 18:07:54 by jlohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

mlx_image_t	*init_image(mlx_t *mlx, t_rect dim)
{
	mlx_image_t	*img;

	img = mlx_new_image(mlx, dim.width, dim.height);
	if (img == NULL)
		mlx_panic();
	if (mlx_image_to_window(mlx, img, dim.x, dim.y) < 0)
	{
		mlx_delete_image(mlx, img);
		mlx_panic();
	}
	return (img);
}

static void	fill_pixbuf(mlx_texture_t *pixbuf, t_map *map)
{
	t_color			white = (t_color){0xFFEEEEEE};
	t_color			black = (t_color){0xFF000000};
	void			*dst;
	t_point			data;
	uint32_t		h;

	data.y = 0;
	while (data.y < map->height)
	{
		data.x = 0;
		while (data.x < map->width)
		{
			dst = pixbuf->pixels
				+ (data.y * pixbuf->width + data.x) * BLOCK_SIZE * BPP;
			if (map->data[data.y * map->width + data.x] == '1')
				universal_memset(dst, &white.pixel, BPP, BLOCK_SIZE);
			else
				universal_memset(dst, &black.pixel, BPP, BLOCK_SIZE);
			++data.x;
		}
		h = 0;
		while (h < BLOCK_SIZE)
		{
			dst = pixbuf->pixels + data.y * pixbuf->width * BLOCK_SIZE * BPP;
			ft_memcpy(dst + h * pixbuf->width * BPP, dst, pixbuf->width * BPP);
			++h;
		}
		++data.y;
	}
}

mlx_texture_t	*init_map_pixbuf(t_map *map)
{
	mlx_texture_t	*pixbuf;

	pixbuf = malloc(sizeof(mlx_texture_t));
	if (pixbuf == NULL)
		return (NULL);
	pixbuf->width = map->width * BLOCK_SIZE;
	pixbuf->height = map->height * BLOCK_SIZE;
	pixbuf->bytes_per_pixel = BPP;
	pixbuf->pixels = malloc(pixbuf->width * pixbuf->height * BPP);
	if (pixbuf->pixels == NULL)
	{
		free(pixbuf);
		return (NULL);
	}
	fill_pixbuf(pixbuf, map);
	return (pixbuf);
}

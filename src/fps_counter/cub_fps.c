/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_fps.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 17:02:11 by pharbst           #+#    #+#             */
/*   Updated: 2023/04/26 18:29:58 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "font.h"

static void	mlx_draw_char(mlx_image_t *image, int32_t texoffset,
		int32_t imgoffset)
{
	uint8_t		*pixelx;
	uint8_t		*pixeli;
	uint32_t	y;

	y = 0;
	if (texoffset < 0)
		return ;
	while (y < FONT_HEIGHT)
	{
		pixelx = &font_atlas.pixels[(y * font_atlas.width
				+ texoffset) * sizeof(int32_t)];
		pixeli = image->pixels + ((y * image->width
					+ imgoffset) * sizeof(int32_t));
		ft_memcpy(pixeli, pixelx, FONT_WIDTH * sizeof(int32_t));
		y++;
	}
}

void	cub_fps(t_scene *scene)
{
	int		fps;
	char	*fps_str;
	int		i;

	fps = fps_counter();
	if (fps != -1)
	{
		fps_str = ft_itoa(fps);
		i = ft_strlen(fps_str);
		while (--i >= 0)
			mlx_draw_char(scene->fps_screen, mlx_get_texoffset(fps_str[i]),
				(i * FONT_WIDTH));
	}
}

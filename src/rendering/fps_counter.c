/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps_counter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlohmann <jlohmann@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 17:02:11 by pharbst           #+#    #+#             */
/*   Updated: 2023/05/03 03:52:33 by jlohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "font.h"

static void	mlx_draw_char(mlx_image_t *image, int32_t tex_off, int32_t img_off)
{
	uint8_t		*pixelx;
	uint8_t		*pixeli;
	uint32_t	y;

	y = 0;
	if (tex_off < 0)
		return ;
	while (y < FONT_HEIGHT)
	{
		pixelx = &font_atlas.pixels[(y * font_atlas.width + tex_off) * BPP];
		pixeli = image->pixels + ((y * image->width + img_off) * BPP);
		ft_memcpy(pixeli, pixelx, FONT_WIDTH * BPP);
		y++;
	}
}

static void	mlx_draw_sting(mlx_image_t *image, const char *str)
{
	int32_t	img_off;
	int32_t	i;

	i = 0;
	img_off = 0;
	if (!str)
		return ;
	while (str[i])
	{
		mlx_draw_char(image, mlx_get_texoffset(str[i]), img_off);
		img_off += FONT_WIDTH;
		i++;
	}
}

void	fps_draw(mlx_image_t *img, double delta_time)
{
	static double	prev_t = 0;
	static double	fps_mid;
	double			t;
	char			*str;

	t = mlx_get_time();
	if (prev_t == 0)
	{
		prev_t = t;
		fps_mid = 1 / delta_time;
		return ;
	}
	fps_mid = ((1 / delta_time) + fps_mid) / 2;
	if (t > prev_t + 1)
	{
		str = ft_itoa((int)round(fps_mid));
		mlx_draw_sting(img, str);
		free(str);
		prev_t = t;
		fps_mid = 1 / delta_time;
	}
}

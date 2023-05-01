/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_fps.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 17:02:11 by pharbst           #+#    #+#             */
/*   Updated: 2023/04/30 14:25:19 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "font.h"
#include <sys/time.h>

typedef struct s_fps
{
	uint64_t	prev_s;
	uint64_t	t;
	double		fps_mid;
}	t_fps;

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

static void	mlx_draw_sting(mlx_image_t *image, const char *str)
{
	int32_t	image_off;
	int32_t	i;

	i = 0;
	image_off = 0;
	if (!str)
		return ;
	while (str[i])
	{
		mlx_draw_char(image, mlx_get_texoffset(str[i]), image_off);
		image_off += FONT_WIDTH;
		i++;
	}
}

static unsigned long	utime(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000000 + tv.tv_usec);
}

void	cub_fps(t_scene *scene)
{
	static uint64_t	prev_s;
	uint64_t		t;
	static double	fps_mid;
	char			*str;

	t = utime();
	if (!prev_s)
	{
		prev_s = t;
		fps_mid = 1 / scene->mlx->delta_time;
		return ;
	}
	else
		fps_mid = ((1 / scene->mlx->delta_time) + fps_mid) / 2;
	if (prev_s + 1000000 < t)
	{
		str = ft_itoa((int)fps_mid);
		printf("debug\n");
		mlx_draw_sting(scene->fps_screen, str);
		// free(str);
		prev_s = 0;
	}
}

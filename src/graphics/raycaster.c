/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlohmann <jlohmann@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 13:33:34 by jlohmann          #+#    #+#             */
/*   Updated: 2023/04/20 14:34:29 by jlohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static	void	set_dda_params(t_dda_params *ddap, t_player *player, int x)
{
	ddap->camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
	ddap->ray_dir = (t_vec){
		player->dir.x + player->plane.x * ddap->camera_x,
		player->dir.y + player->plane.y * ddap->camera_x
	};
	ddap->block_pos = (t_point){player->pos.x, player->pos.y};
	ddap->delta = (t_vec){99999999, 99999999};
	if (ddap->ray_dir.x != 0)
		ddap->delta.x = fabs(1 / ddap->ray_dir.x);
	if (ddap->ray_dir.y != 0)
		ddap->delta.y = fabs(1 / ddap->ray_dir.y);
	ddap->step_dir = (t_point){
		2 * (ddap->ray_dir.x > 0) - 1,
		2 * (ddap->ray_dir.y > 0) - 1
	};
	if (ddap->ray_dir.x < 0)
		ddap->dist.x = (player->pos.x - ddap->block_pos.x) * ddap->delta.x;
	else
		ddap->dist.x = (1 - player->pos.x + ddap->block_pos.x) * ddap->delta.x;
	if (ddap->ray_dir.y < 0)
		ddap->dist.y = (player->pos.y - ddap->block_pos.y) * ddap->delta.y;
	else
		ddap->dist.y = (1 - player->pos.y + ddap->block_pos.y) * ddap->delta.y;
}

t_hit_info	ray_cast(int x, t_player *player, t_map *map)
{
	t_dda_params	ddap;
	t_hit_info		hit;

	set_dda_params(&ddap, player, x);
	while (true)
	{
		if (ddap.dist.x < ddap.dist.y)
		{
			ddap.dist.x += ddap.delta.x;
			ddap.block_pos.x += ddap.step_dir.x;
			hit.side = 0;
		}
		else
		{
			ddap.dist.y += ddap.delta.y;
			ddap.block_pos.y += ddap.step_dir.y;
			hit.side = 1;
		}
		if (map->data[ddap.block_pos.y * map->width + ddap.block_pos.x] > '0')
			break ;
	}
	if (hit.side == 0)
		hit.dist = ddap.dist.x - ddap.delta.x;
	else
		hit.dist = ddap.dist.y - ddap.delta.y;
	if ((hit.side == 0 && ddap.step_dir.x < 0) || (hit.side == 1 && ddap.step_dir.y < 0))
		hit.side += 2;
	hit.pos = vec_add(player->pos, vec_scale(ddap.ray_dir, hit.dist));
	hit.block_pos = ddap.block_pos;
	return (hit);
}

/* void	draw_wall_line(mlx_image_t *screen, int32_t x, double dist, uint32_t color)
{
	int		line_height;
	int		start;
	int		end;

	if (dist == 0)
		line_height = SCREEN_HEIGHT;
	else
		line_height = SCREEN_HEIGHT / dist;
	start = -line_height / 2 + 0.75 * SCREEN_HEIGHT;
	end = line_height / 2 + 0.75 * SCREEN_HEIGHT;
	start *= (start >= 0);
	if (end > 1.5 * SCREEN_HEIGHT)
		end = 1.5 * SCREEN_HEIGHT;
	if (dist == 0)
		//color = color_change_lightness(color, 1);
		color_change_lightness(color, 1);
	else
		color = color_change_lightness(color, 2 / dist);
	while (start != end)
	{
		mlx_put_pixel(screen, x, start, color);
		++start;
	}
} */

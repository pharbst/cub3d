/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlohmann <jlohmann@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 13:33:34 by jlohmann          #+#    #+#             */
/*   Updated: 2023/05/03 02:44:55 by jlohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_dda_params	set_dda_params(t_player *player, t_vec ray_dir)
{
	t_dda_params	ddap;

	ddap.ray_dir = ray_dir;
	ddap.tile_pos = (t_point){player->pos.x, player->pos.y};
	ddap.delta = (t_vec){99999999, 99999999};
	if (ddap.ray_dir.x != 0)
		ddap.delta.x = fabs(1 / ddap.ray_dir.x);
	if (ddap.ray_dir.y != 0)
		ddap.delta.y = fabs(1 / ddap.ray_dir.y);
	ddap.step_dir = (t_point){
		2 * (ddap.ray_dir.x > 0) - 1,
		2 * (ddap.ray_dir.y > 0) - 1
	};
	if (ddap.ray_dir.x < 0)
		ddap.dist.x = (player->pos.x - ddap.tile_pos.x) * ddap.delta.x;
	else
		ddap.dist.x = (1 - player->pos.x + ddap.tile_pos.x) * ddap.delta.x;
	if (ddap.ray_dir.y < 0)
		ddap.dist.y = (player->pos.y - ddap.tile_pos.y) * ddap.delta.y;
	else
		ddap.dist.y = (1 - player->pos.y + ddap.tile_pos.y) * ddap.delta.y;
	return (ddap);
}

static t_hit_info	ray_walk(t_dda_params ddap, t_map *map)
{
	t_hit_info	hit;

	while (true)
	{
		if (ddap.dist.x < ddap.dist.y)
		{
			ddap.dist.x += ddap.delta.x;
			ddap.tile_pos.x += ddap.step_dir.x;
			hit.side = 0;
		}
		else
		{
			ddap.dist.y += ddap.delta.y;
			ddap.tile_pos.y += ddap.step_dir.y;
			hit.side = 1;
		}
		if (map->data[ddap.tile_pos.y * map->width + ddap.tile_pos.x] > '0')
			break ;
	}
	if (hit.side == 0)
		hit.dist = ddap.dist.x - ddap.delta.x;
	else
		hit.dist = ddap.dist.y - ddap.delta.y;
	return (hit);
}

t_hit_info	ray_cast(t_player *player, t_map *map, t_vec ray_dir)
{
	t_dda_params	ddap;
	t_hit_info		hit;

	ddap = set_dda_params(player, ray_dir);
	hit = ray_walk(ddap, map);
	if ((hit.side == 0 && ddap.step_dir.x < 0)
		|| (hit.side == 1 && ddap.step_dir.y < 0))
		hit.side += 2;
	hit.pos = vec_add(player->pos, vec_scale(ddap.ray_dir, hit.dist));
	return (hit);
}

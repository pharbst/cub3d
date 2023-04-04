/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlohmann <jlohmann@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 13:33:34 by jlohmann          #+#    #+#             */
/*   Updated: 2023/04/04 18:15:24 by jlohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static	void	set_dda_params(t_player *player, t_dda_params *ddap, int x)
{
	ddap->camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
	ddap->ray_dir = (t_vec){
		player->dir.x + player->plane.x * ddap->camera_x,
		player->dir.y + player->plane.y * ddap->camera_x
	};
	ddap->step_pos = (t_point){player->pos.x, player->pos.y};
	ddap->delta = (t_vec){99999999, 99999999};
	if (ddap->ray_dir.x != 0)
		ddap->delta.x = fabs(1 / ddap->ray_dir.x);
	if (ddap->ray_dir.y != 0)
		ddap->delta.y = fabs(1 / ddap->ray_dir.x);
	ddap->step_dir = (t_point){
		2 * (ddap->ray_dir.x > 0) - 1,
		2 * (ddap->ray_dir.y > 0) - 1
	};
	if (ddap->ray_dir.x < 0)
		ddap->dist.x = (player->pos.x - ddap->step_pos.x) * ddap->delta.x;
	else
		ddap->dist.x = (1 - player->pos.x + ddap->step_pos.x) * ddap->delta.x;
	if (ddap->ray_dir.y < 0)
		ddap->dist.y = (player->pos.y - ddap->step_pos.y) * ddap->delta.y;
	else
		ddap->dist.y = (1 - player->pos.y + ddap->step_pos.y) * ddap->delta.y;
}

static double	perform_dda(t_dda_params *ddap, t_map *map)
{
	int		side;

	while (true)
	{
		if (ddap->dist.x < ddap->dist.y)
		{
			ddap->dist.x += ddap->delta.x;
			ddap->step_pos.x += ddap->step_dir.x;
			side = 0;
		}
		else
		{
			ddap->dist.y += ddap->delta.y;
			ddap->step_pos.y += ddap->step_dir.y;
			side = 1;
		}
		if (map->data[ddap->step_pos.y * map->height + ddap->step_pos.x] > 0)
			break;
	}
	if (side == 0)
		return (ddap->dist.x - ddap->delta.x);
	return (ddap->dist.y - ddap->delta.y);
}

void	raycast(t_player *player, t_map *map, t_scene *scene)
{
	t_dda_params	ddap;
	int				x;
	double			dist;

	int				line_height;
	t_point			start;
	t_point			end;
	
	x = 0;
	while (x < SCREEN_WIDTH)
	{
		set_dda_params(player, &ddap, x);
		dist = perform_dda(&ddap, map);
		line_height = SCREEN_HEIGHT / dist;
		start = (t_point){x, -line_height / 2 + SCREEN_HEIGHT / 2};
		end = (t_point){x, line_height / 2 + SCREEN_HEIGHT / 2};
		draw_line(scene->screen, start, end, 0x00AA00FF);
		++x;
	}
}

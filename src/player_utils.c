/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlohmann <jlohmann@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 14:33:11 by jlohmann          #+#    #+#             */
/*   Updated: 2023/04/11 20:16:56 by jlohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_vec	collision_correction(t_map *map, t_vec pos, t_vec step)
{
	t_vec	coll_h;
	t_vec	coll_v;
	t_vec	new_pos;

	coll_h = vec_add(pos, (t_vec){step.x, 0});
	coll_h = vec_add(pos, (t_vec){0, step.y});
	if (map->data[(int)coll_h.y * map->width + (int)coll_h.x])
	return ();
}

void	player_move(t_keystate *state, t_player *player, t_map *map)
{
	t_vec	step;

	step = player->dir;
	if (state->W && state->A)
		step = vec_rotate(step, -M_PI_4);
	else if (state->W && state->D)
		step = vec_rotate(step, M_PI_4);
	else if (state->S && state->A)
		step = vec_rotate(step, -3 * M_PI_4);
	else if (state->S && state->D)
		step = vec_rotate(step, 3 * M_PI_4);
	else if (state->A)
		step = vec_rotate(step, -M_PI_2);
	else if (state->S)
		step = vec_rotate(step, -M_PI);
	else if (state->D)
		step = vec_rotate(step, M_PI_2);
	else if (!state->W)
		return ;
	step = collision_correction(map, player->pos, step);
	if (state->SHIFT)
		step = vec_scale(step, 2 * MOVE_SPEED);
	else
		step = vec_scale(step, MOVE_SPEED);
	player->pos = step;
}

void	player_rotate(t_keystate *state, t_player *player)
{
	
	if (state->LEFT)
	{
		player->dir = vec_rotate(player->dir, -ROT_SPEED);
		player->plane = vec_rotate(player->plane, -ROT_SPEED);
	}
	else if (state->RIGHT)
	{
		player->dir = vec_rotate(player->dir, ROT_SPEED);
		player->plane = vec_rotate(player->plane, ROT_SPEED);
	}
}
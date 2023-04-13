/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlohmann <jlohmann@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 14:33:11 by jlohmann          #+#    #+#             */
/*   Updated: 2023/04/14 01:36:35 by jlohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_vec	collision_correction(t_map *map, t_vec pos, t_vec step)
{
	t_vec	target;
	t_vec	new_step;

	new_step = step;
	target = vec_add(pos, vec_scale(step, 0.5));
	if (map->data[(int)pos.y * map->width + (int)target.x])
		new_step.x = 0;
	if (map->data[(int)target.y * map->width + (int)pos.x])
		new_step.y = 0;
	return (new_step);
}

void	player_move(t_keystate *state, t_player *player, t_map *map)
{
	t_vec	step;

	step = player->dir;
	if (state->w && state->a)
		step = vec_rotate(step, -M_PI_4);
	else if (state->w && state->d)
		step = vec_rotate(step, M_PI_4);
	else if (state->s && state->a)
		step = vec_rotate(step, -3 * M_PI_4);
	else if (state->s && state->d)
		step = vec_rotate(step, 3 * M_PI_4);
	else if (state->a)
		step = vec_rotate(step, -M_PI_2);
	else if (state->s)
		step = vec_rotate(step, -M_PI);
	else if (state->d)
		step = vec_rotate(step, M_PI_2);
	else if (!state->w)
		return ;
	step = collision_correction(map, player->pos, step);
	if (state->shift)
		step = vec_scale(step, 2 * MOVE_SPEED);
	else
		step = vec_scale(step, MOVE_SPEED);
	player->pos = vec_add(player->pos, step);
}

void	player_rotate(t_keystate *state, t_player *player)
{
	if (state->left)
	{
		player->dir = vec_rotate(player->dir, -ROT_SPEED);
		player->plane = vec_rotate(player->plane, -ROT_SPEED);
	}
	else if (state->right)
	{
		player->dir = vec_rotate(player->dir, ROT_SPEED);
		player->plane = vec_rotate(player->plane, ROT_SPEED);
	}
}

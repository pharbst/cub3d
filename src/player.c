/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlohmann <jlohmann@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 10:16:45 by jlohmann          #+#    #+#             */
/*   Updated: 2023/04/27 21:48:33 by jlohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_vec	collision_correction(t_vec pos, t_vec step, t_map *map)
{
	t_vec	new_step;
	t_vec	target;

	new_step = step;
	target = vec_add(pos, vec_scale(step, 0.5));
	if (map->data[(int)pos.y * map->width + (int)target.x] > '0')
		new_step.x = 0;
	if (map->data[(int)target.y * map->width + (int)pos.x] > '0')
		new_step.y = 0;
	return (new_step);
}

static t_vec	player_move(t_keystate *state, t_vec step, t_vec pos, t_map *map)
{
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
		return (pos);
	if (!state->alt)
		step = collision_correction(pos, step, map);
	if (state->shift)
		step = vec_scale(step, 2 * MOVE_SPEED);
	else
		step = vec_scale(step, MOVE_SPEED);
	return (vec_add(pos, step));
}

static void	player_rotate(t_keystate *state, t_player *player)
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

void	player_init(t_player *player)
{
	player->fov = FOV;
	player->plane = vec_scale(vec_rotate(player->dir, M_PI_2), player->fov);
}

void	player_update(mlx_t *mlx, t_player *player, t_map *map)
{
	t_keystate	state;

	state = input_get_keys(mlx);
	player->pos = player_move(&state, player->dir, player->pos, map);
	player_rotate(&state, player);
}

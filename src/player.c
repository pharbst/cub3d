/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlohmann <jlohmann@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 10:16:45 by jlohmann          #+#    #+#             */
/*   Updated: 2023/05/02 20:15:55 by jlohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_vec	collision_correction(t_player *player, t_vec step, t_map *map)
{
	t_vec		new_step;
	t_vec		target;

	new_step = step;
	target = vec_add(player->pos, vec_scale(step, 0.3));
	if (map->data[(int)player->pos.y * map->width + (int)target.x] > '0')
		new_step.x = 0;
	if (map->data[(int)target.y * map->width + (int)player->pos.x] > '0')
		new_step.y = 0;
	if (map->data[(int)target.y * map->width + (int)target.x] > '0'
		&& new_step.x != 0 && new_step.y != 0)
	{
		if (ray_cast(player, map, step).side % 2 == 0)
			new_step.x = 0;
		else
			new_step.y = 0;
	}
	return (new_step);
}

static t_vec	set_step_dir(t_vec step, t_keys keys)
{
	if (keys.w && keys.a)
		step = vec_rotate(step, -M_PI_4);
	else if (keys.w && keys.d)
		step = vec_rotate(step, M_PI_4);
	else if (keys.s && keys.a)
		step = vec_rotate(step, -3 * M_PI_4);
	else if (keys.s && keys.d)
		step = vec_rotate(step, 3 * M_PI_4);
	else if (keys.a)
		step = vec_rotate(step, -M_PI_2);
	else if (keys.s)
		step = vec_rotate(step, -M_PI);
	else if (keys.d)
		step = vec_rotate(step, M_PI_2);
	else if (!keys.w)
		return ((t_vec){0, 0});
	return (step);
}

static void	player_rotate(t_keys *keys, t_player *player)
{
	if (keys->left)
	{
		player->dir = vec_rotate(player->dir, -ROT_SPEED);
		player->plane = vec_rotate(player->plane, -ROT_SPEED);
	}
	else if (keys->right)
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
	t_keys	keys;
	t_vec	step;

	keys = input_get_keys(mlx);
	step = set_step_dir(player->dir, keys);
	if (!keys.alt)
		step = collision_correction(player, step, map);
	if (keys.shift)
		step = vec_scale(step, 2);
	step = vec_scale(step, MOVE_SPEED);
	player->pos = vec_add(player->pos, step);
	player_rotate(&keys, player);
}

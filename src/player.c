/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlohmann <jlohmann@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 10:16:45 by jlohmann          #+#    #+#             */
/*   Updated: 2023/04/27 20:51:56 by jlohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

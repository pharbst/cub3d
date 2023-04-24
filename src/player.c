/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlohmann <jlohmann@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 10:16:45 by jlohmann          #+#    #+#             */
/*   Updated: 2023/04/24 17:54:19 by jlohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	player_init(t_player *player)
{
	player->fov = FOV;
	player->plane = vec_rotate((t_vec){player->dir.x * player->fov, player->dir.y * player->fov}, M_PI_2);
}

void	player_update(mlx_t *mlx, t_player *player, t_map *map)
{
	t_keystate	state;

	state = input_get_keys(mlx);
	player_move(&state, player, map);
	player_rotate(&state, player);
}

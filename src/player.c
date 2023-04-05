/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlohmann <jlohmann@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 10:16:45 by jlohmann          #+#    #+#             */
/*   Updated: 2023/04/05 16:39:03 by jlohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	player_init(mlx_t *mlx, t_player *player, t_vec pos, t_vec dir)
{
	player->pos = pos;
	player->dir = dir;
	player->plane = vec_rotate((t_vec){player->dir.x * FOV, player->dir.y * FOV}, M_PI_2);
	player->img = init_image(mlx, player->pos.x, player->pos.y, 32, 32);
}

void	player_update(mlx_t *mlx, t_player *player)
{
	t_vec	step;
	bool	key_state[7];

	key_state[0] = mlx_is_key_down(mlx, MLX_KEY_W);
	key_state[1] = mlx_is_key_down(mlx, MLX_KEY_A);
	key_state[2] = mlx_is_key_down(mlx, MLX_KEY_S);
	key_state[3] = mlx_is_key_down(mlx, MLX_KEY_D);
	key_state[4] = mlx_is_key_down(mlx, MLX_KEY_LEFT);
	key_state[5] = mlx_is_key_down(mlx, MLX_KEY_RIGHT);
	key_state[6] = mlx_is_key_down(mlx, MLX_KEY_LEFT_SHIFT);

	if (key_state[4])
	{
		player->dir = vec_rotate(player->dir, -ROT_SPEED);
		player->plane = vec_rotate(player->plane, -ROT_SPEED);
	}
	else if (key_state[5])
	{
		player->dir = vec_rotate(player->dir, ROT_SPEED);
		player->plane = vec_rotate(player->plane, ROT_SPEED);
	}
	step = vec_scale(player->dir, MOVE_SPEED);
	if (key_state[6])
		step = vec_scale(step, 2);
	if (key_state[0] && key_state[1])
		step = vec_rotate(step, -M_PI_4);
	else if (key_state[0] && key_state[3])
		step = vec_rotate(step, M_PI_4);
	else if (key_state[2] && key_state[1])
		step = vec_rotate(step, -3 * M_PI_4);
	else if (key_state[2] && key_state[3])
		step = vec_rotate(step, 3 * M_PI_4);
	else if (key_state[0])
		;
	else if (key_state[1])
		step = vec_rotate(step, -M_PI_2);
	else if (key_state[2])
		step = vec_rotate(step, -M_PI);
	else if (key_state[3])
		step = vec_rotate(step, M_PI_2);
	else 
		return ;
	player->pos = vec_add(player->pos, step);
}

void	player_draw(t_player *player, t_map *map)
{
	const t_point	offset = (t_point){
		player->img->width / 2, player->img->height / 2
	};

	draw_fill(player->img, 0x00000000);
	player->img->instances[0].x = player->pos.x * MAP_WIDTH / map->width + map->img->instances[0].x - offset.x; // round pos for smoother movement?
	player->img->instances[0].y = player->pos.y * MAP_HEIGHT / map->height + map->img->instances[0].y - offset.y;
	draw_point(player->img, offset, 3, 0x00AA00FF);
	draw_triangle(player->img,
		(t_point){
			offset.x,
			offset.y
		},
		(t_point){
			offset.x + player->dir.x * 8 + player->plane.x * 8,
			offset.y + player->dir.y * 8 + player->plane.y * 8
		},
		(t_point){
			offset.x + player->dir.x * 8 + -player->plane.x * 8,
			offset.y + player->dir.y * 8 + -player->plane.y * 8
		},
		0xFFFF00FF
	);
}

void	player_destroy(mlx_t *mlx, t_player *player)
{
	mlx_delete_image(mlx, player->img);
}

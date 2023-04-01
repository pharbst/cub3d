/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlohmann <jlohmann@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 10:16:45 by jlohmann          #+#    #+#             */
/*   Updated: 2023/04/01 17:34:35 by jlohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	player_init(mlx_t *mlx, t_player *player, t_vec pos, t_vec dir)
{
	player->pos = pos;
	player->dir = dir;
	player->plane = vec_rotate((t_vec){player->dir.x * FOV, player->dir.y * FOV}, M_PI_2);
	player->img = mlx_new_image(mlx, 32, 32);
	if (player->img == NULL)
		mlx_panic();
	if (mlx_image_to_window(mlx, player->img, player->pos.x, player->pos.y) < 0)
		mlx_panic();
}

void	player_update(mlx_t *mlx, t_player *player)
{
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
	{
		player->pos.x += player->dir.x * MOVE_SPEED;
		player->pos.y += player->dir.y * MOVE_SPEED;
	}
	else if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
	{
		player->pos.x -= player->dir.x * MOVE_SPEED;
		player->pos.y -= player->dir.y * MOVE_SPEED;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
	{
		player->dir = vec_rotate(player->dir, -ROT_SPEED);
		player->plane = vec_rotate(player->plane, -ROT_SPEED);
	}
	else if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
	{
		player->dir = vec_rotate(player->dir, ROT_SPEED);
		player->plane = vec_rotate(player->plane, ROT_SPEED);
	}
}

void	player_draw(t_player *player, t_map *map)
{
	const t_point	offset = (t_point){
		player->img->width / 2, player->img->height / 2
	};

	draw_fill(player->img, 0x00000000);
	player->img->instances[0].x = player->pos.x * MAP_WIDTH / map->width - offset.x; // round pos for smoother movement?
	player->img->instances[0].y = player->pos.y * MAP_HEIGHT / map->height - offset.y;
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

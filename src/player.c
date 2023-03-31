/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlohmann <jlohmann@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 10:16:45 by jlohmann          #+#    #+#             */
/*   Updated: 2023/03/31 12:50:58 by jlohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	player_init(mlx_t *mlx, t_player *player, t_vec pos, t_vec dir)
{
	player->pos = pos;
	player->dir = dir;
	player->plane = vec_rotate(player->dir, M_PI_2);
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
		player->pos.x += player->dir.x;
		player->pos.y += player->dir.y;
	}
	else if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
	{
		player->pos.x -= player->dir.x;
		player->pos.y -= player->dir.y;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
	{
		player->dir = vec_rotate(player->dir, -ROT_SPEED);
		player->plane = vec_rotate(player->dir, M_PI_2);
	}
	else if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
	{
		player->dir = vec_rotate(player->dir, ROT_SPEED);
		player->plane = vec_rotate(player->dir, M_PI_2);
	}
}

void	player_draw(t_player *player)
{
	const t_point	offset = (t_point){
		player->img->width / 2, player->img->height / 2
	};

	draw_fill(player->img, 0x00000000);
	player->img->instances[0].x = player->pos.x - offset.x; // round pos for smoother movement?
	player->img->instances[0].y = player->pos.y - offset.y;
	draw_point(player->img, offset, 4, 0x00AA00FF);
	draw_line(player->img, offset, (t_point){offset.x + player->dir.x * 8, offset.y + player->dir.y * 8}, 0x00AA00FF);
	draw_line(player->img,
		(t_point){
			offset.x + player->dir.x * 8 + player->plane.x * 8,
			offset.y + player->dir.y * 8 + player->plane.y * 8},
		(t_point){
			offset.x + player->dir.x * 8 + -player->plane.x * 8,
			offset.y + player->dir.y * 8 + -player->plane.y * 8},
		0xFF0000FF
	);
}

void	player_destroy(mlx_t *mlx, t_player *player)
{
	mlx_delete_image(mlx, player->img);
}

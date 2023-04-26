/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlohmann <jlohmann@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 14:06:51 by jlohmann          #+#    #+#             */
/*   Updated: 2023/04/27 01:00:04 by jlohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_keystate	input_get_keys(mlx_t *mlx)
{
	t_keystate	state;

	state.w = mlx_is_key_down(mlx, MLX_KEY_W);
	state.a = mlx_is_key_down(mlx, MLX_KEY_A);
	state.s = mlx_is_key_down(mlx, MLX_KEY_S);
	state.d = mlx_is_key_down(mlx, MLX_KEY_D);
	state.left = mlx_is_key_down(mlx, MLX_KEY_LEFT);
	state.right = mlx_is_key_down(mlx, MLX_KEY_RIGHT);
	state.shift = mlx_is_key_down(mlx, MLX_KEY_LEFT_SHIFT);
	state.alt = mlx_is_key_down(mlx, MLX_KEY_LEFT_ALT);
	return (state);
}

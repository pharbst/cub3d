/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlohmann <jlohmann@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 14:06:51 by jlohmann          #+#    #+#             */
/*   Updated: 2023/04/07 14:36:48 by jlohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_keystate	input_get_keys(mlx_t *mlx)
{
	t_keystate state;

	state.W = mlx_is_key_down(mlx, MLX_KEY_W);
	state.A = mlx_is_key_down(mlx, MLX_KEY_A);
	state.S = mlx_is_key_down(mlx, MLX_KEY_S);
	state.D = mlx_is_key_down(mlx, MLX_KEY_D);
	state.LEFT = mlx_is_key_down(mlx, MLX_KEY_LEFT);
	state.RIGHT = mlx_is_key_down(mlx, MLX_KEY_RIGHT);
	state.SHIFT = mlx_is_key_down(mlx, MLX_KEY_LEFT_SHIFT);
	return (state);
}
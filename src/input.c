/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlohmann <jlohmann@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 14:06:51 by jlohmann          #+#    #+#             */
/*   Updated: 2023/05/02 13:31:38 by jlohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_keys	input_get_keys(mlx_t *mlx)
{
	t_keys	keys;

	keys.w = mlx_is_key_down(mlx, MLX_KEY_W);
	keys.a = mlx_is_key_down(mlx, MLX_KEY_A);
	keys.s = mlx_is_key_down(mlx, MLX_KEY_S);
	keys.d = mlx_is_key_down(mlx, MLX_KEY_D);
	keys.left = mlx_is_key_down(mlx, MLX_KEY_LEFT);
	keys.right = mlx_is_key_down(mlx, MLX_KEY_RIGHT);
	keys.shift = mlx_is_key_down(mlx, MLX_KEY_LEFT_SHIFT);
	keys.alt = mlx_is_key_down(mlx, MLX_KEY_LEFT_ALT);
	return (keys);
}

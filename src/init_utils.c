/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlohmann <jlohmann@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 12:20:31 by jlohmann          #+#    #+#             */
/*   Updated: 2023/04/01 20:25:09 by jlohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

mlx_image_t	*init_image(mlx_t *mlx, int32_t x, int32_t y, uint32_t width, uint32_t height)
{
	mlx_image_t	*img;

	img = mlx_new_image(mlx, width, height);
	if (img == NULL)
		mlx_panic();
	if (mlx_image_to_window(mlx, img, x, y) < 0)
	{
		mlx_delete_image(mlx, img);
		mlx_panic();
	}
	return (img);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlohmann <jlohmann@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 12:20:31 by jlohmann          #+#    #+#             */
/*   Updated: 2023/04/27 20:38:56 by jlohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

mlx_image_t	*init_image(mlx_t *mlx, t_rect dim)
{
	mlx_image_t	*img;

	img = mlx_new_image(mlx, dim.width, dim.height);
	if (img == NULL)
		mlx_panic();
	if (mlx_image_to_window(mlx, img, dim.x, dim.y) < 0)
	{
		mlx_delete_image(mlx, img);
		mlx_panic();
	}
	return (img);
}

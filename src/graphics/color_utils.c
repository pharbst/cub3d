/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlohmann <jlohmann@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 15:42:13 by jlohmann          #+#    #+#             */
/*   Updated: 2023/04/27 20:48:53 by jlohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_pixel	color_dim(t_pixel color, double factor)
{
	t_pixel	new_color;

	if (factor > 1)
		factor = 1;
	else if (factor < 0)
		factor = 0;
	new_color.r = color.r * factor;
	new_color.g = color.g * factor;
	new_color.b = color.b * factor;
	new_color.a = 0xFF;
	return (new_color);
}

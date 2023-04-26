/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlohmann <jlohmann@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 15:42:13 by jlohmann          #+#    #+#             */
/*   Updated: 2023/04/25 16:12:49 by jlohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_pixel	color_change_lightness(t_pixel color, double lightness)
{
	t_pixel	new_color;

	if (lightness > 1)
		lightness = 1;
	else if (lightness < 0)
		lightness = 0;
	new_color.r = color.r * lightness;
	new_color.g = color.g * lightness;
	new_color.b = color.b * lightness;
	new_color.a = 0xFF;
	return (new_color);
}

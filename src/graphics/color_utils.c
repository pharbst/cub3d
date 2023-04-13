/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlohmann <jlohmann@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 15:42:13 by jlohmann          #+#    #+#             */
/*   Updated: 2023/04/13 17:39:14 by jlohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

uint32_t	color_change_lightness(uint32_t color, double lightness)
{
	uint32_t	new_color;
	uint8_t		*area;

	if (lightness > 1)
		lightness = 1;
	else if (lightness < 0)
		return (0x000000FF);
	area = (uint8_t *)&new_color + 3;
	*(area--) = ((uint8_t)(color >> 24) * lightness);
	*(area--) = ((uint8_t)(color >> 16) * lightness);
	*(area--) = ((uint8_t)(color >> 8) * lightness);
	*(area--) = ((uint8_t)(color & 0xFF));
	return (new_color);
}

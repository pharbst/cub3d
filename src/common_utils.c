/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlohmann <jlohmann@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 12:00:56 by jlohmann          #+#    #+#             */
/*   Updated: 2023/03/31 12:22:53 by jlohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_vec	vec_rotate(t_vec vec, double angle)
{
	t_vec	new;
	new.x = vec.x * cos(angle) - vec.y * sin(angle);
	new.y = vec.x * sin(angle) + vec.y * cos(angle);
	return (new);
}

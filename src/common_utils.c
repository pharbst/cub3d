/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlohmann <jlohmann@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 12:00:56 by jlohmann          #+#    #+#             */
/*   Updated: 2023/04/27 20:52:18 by jlohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_vec	vec_add(t_vec a, t_vec b)
{
	return ((t_vec){a.x + b.x, a.y + b.y});
}

t_vec	vec_scale(t_vec vec, double factor)
{
	return ((t_vec){vec.x * factor, vec.y * factor});
}

t_vec	vec_rotate(t_vec vec, double angle)
{
	t_vec	new;

	new.x = vec.x * cos(angle) - vec.y * sin(angle);
	new.y = vec.x * sin(angle) + vec.y * cos(angle);
	return (new);
}

void	universal_memset(void *dst, void *src, size_t size, size_t len)
{
	while (len > 0)
	{
		ft_memcpy(dst, src, size);
		dst += size;
		--len;
	}
}

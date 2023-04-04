/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 18:31:26 by pharbst           #+#    #+#             */
/*   Updated: 2023/04/04 18:47:18 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_error.h"

int	cub_errno(bool read, int value)
{
	static int	cub_errno;

	if (read)
		return (cub_errno);
	return (cub_errno = value);
}

void	cub_strerror(void)
{
	if (cub_errno(READ, 0) == ERNOID)
		return (ft_putstr_fd("error: unknown identifier for wall texture\n", 2));
	// if (cub_errno(READ, 0) == )
	// 	return (ft_putstr_fd());
	// if (cub_errno(READ, 0) == )
	// 	return (ft_putstr_fd());
	// if (cub_errno(READ, 0) == )
	// 	return (ft_putstr_fd());
	// if (cub_errno(READ, 0) == )
	// 	return (ft_putstr_fd());
	// if (cub_errno(READ, 0) == )
	// 	return (ft_putstr_fd());
}

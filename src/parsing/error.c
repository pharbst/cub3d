/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 18:31:26 by pharbst           #+#    #+#             */
/*   Updated: 2023/04/10 08:02:43 by pharbst          ###   ########.fr       */
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
		return (ft_putstr_fd(_ERNOID, 2));
	else if (cub_errno(READ, 0) == ERNOFILE)
		return (ft_putstr_fd(_ERNOFILE, 2));
	else if (cub_errno(READ, 0) == EREOF)
		return (ft_putstr_fd(_EREOF, 2));
	else if (cub_errno(READ, 0) == ERFORMAT)
		return (ft_putstr_fd(_ERFORMAT, 2));
	else if (cub_errno(READ, 0) == ERALLOC)
		return (ft_putstr_fd(_ERALLOC, 2));
	else if (cub_errno(READ, 0) == EREXT)
		return (ft_putstr_fd(_EREXT, 2));
	else if (cub_errno(READ, 0) == ERARG)
		return (ft_putstr_fd(_ERARG, 2), ft_putstr_fd(_ERARGHELP, 1));
	else if (cub_errno(READ, 0) == ERMULTIPLAY)
		return (ft_putstr_fd(_ERMULTIPLAY, 2));
	else if (cub_errno(READ, 0) == ERNOPLAY)
		return (ft_putstr_fd(_ERNOPLAY, 2));
	else if (cub_errno(READ, 0) == ERMAP)
		return (ft_putstr_fd(_ERMAP, 2));
}

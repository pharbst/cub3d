/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlohmann <jlohmann@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 18:31:26 by pharbst           #+#    #+#             */
/*   Updated: 2023/05/04 17:07:10 by jlohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_error.h"
#include "cub3d.h"

int	cub_errno(bool read, int value)
{
	static int	cub_errno;

	if (read)
		return (cub_errno);
	return (cub_errno = value);
}

char	*cub_errinfo(char *info)
{
	static char	stash[1024];

	if (!info)
		return (stash);
	if (ft_strlen(info) > 1023)
		return (NULL);
	ft_memcpy(stash, info, ft_strlen(info));
	return (stash);
}

void	cub_strerror(void)
{
	if (!cub_errno(READ, 0))
		return ;
	if (cub_errno(READ, 0) == ERNOID)
		return (ft_putstr_fd("error: ", 2), ft_putstr_fd(cub_errinfo(NULL), 2),
			ft_putstr_fd(_ERNOID, 2));
	else if (cub_errno(READ, 0) == ERNOFILE)
		return (ft_putstr_fd("error: ", 2), ft_putstr_fd(cub_errinfo(NULL), 2),
			ft_putstr_fd(_ERNOFILE, 2));
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

int	texture_error(char *tmp)
{
	if (!cub_errinfo(skip_space(tmp)))
		return (cub_errno(WRITE, ERALLOC), 1);
	return (cub_errno(WRITE, ERNOID), 1);
}

int	file_error(char *line)
{
	if (!cub_errinfo(line))
		return (cub_errno(WRITE, ERALLOC), 1);
	return (cub_errno(WRITE, ERNOFILE), 1);
}

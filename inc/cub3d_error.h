/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_error.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 17:59:36 by pharbst           #+#    #+#             */
/*   Updated: 2023/04/13 22:37:57 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_ERROR_H
# define CUB3D_ERROR_H

# include "stdbool.h"
# include <stdarg.h>
# include "libft.h"

# define READ 1
# define WRITE 0

# define ERNOID			1
# define ERNOFILE		2
# define EREOF			3
# define ERFORMAT		4
# define ERALLOC		5
# define EREXT			6
# define ERARG			7
# define ERMULTIPLAY	8
# define ERNOPLAY		9
# define ERMAP			10

# define _ERNOID		" unknown identifier for wall texture\n"
# define _ERNOFILE		" file not found\n"
# define _EREOF			"error: unexpected end of file\n"
# define _ERFORMAT		"error: invalid file format\n"
# define _ERALLOC		"error: memory allocation failed\n"
# define _EREXT			"error: invalid file extension\n"
# define _ERARG			"error: invalid number of arguments\n"
# define _ERARGHELP		"usage: ./cub3d <path to map.cub>\n"
# define _ERMULTIPLAY	"error: multiple player positions\n"
# define _ERNOPLAY		"error: no player position\n"
# define _ERMAP			"error: invalid map\n"

int		cub_errno(bool read, int value);
void	cub_strerror(void);
char	*cub_errinfo(char *info);
int		texture_error(char *tmp);
int		file_error(char *line);

#endif

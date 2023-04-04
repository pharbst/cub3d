/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_error.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 17:59:36 by pharbst           #+#    #+#             */
/*   Updated: 2023/04/04 18:48:40 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_ERROR_H
# define CUB3D_ERROR_H

# include "stdbool.h"
# include <stdarg.h>
# include "libft.h"

# define READ 1
# define WRITE 0
# define ERNOID 1

int		cub_errno(bool read, int value);
void	cub_strerror(void);
void	ft_putstrsfd(int fd, const char *str, ...);

#endif

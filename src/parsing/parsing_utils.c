/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 17:28:40 by pharbst           #+#    #+#             */
/*   Updated: 2023/04/04 18:50:23 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*skip_space(char *line)
{
	if (!line)
		return (NULL);
	while (ft_iswhitespace(*line))
		line++;
	return (line);
}

void	ft_putstrsfd(int fd, const char *str, ...)
{
	va_list	ap;

	va_start(ap, str);
	while (str)
	{
		ft_putstr_fd(str, fd);
		str = va_arg(ap, const char *);
	}
	va_end(ap);
}

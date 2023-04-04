/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 16:13:38 by pharbst           #+#    #+#             */
/*   Updated: 2023/04/04 17:36:57 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	pars(char *path, t_scene *scene)
{
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd < 0 || get_textures(fd, scene) || get_map(fd, scene))
		return (1);
}

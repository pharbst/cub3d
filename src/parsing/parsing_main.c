/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 16:13:38 by pharbst           #+#    #+#             */
/*   Updated: 2023/04/21 13:55:38 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	pars(char *path, t_scene *scene)
{
	int		fd;
	char	*f_exten;

	f_exten = ft_strrchr(path, '.');
	if (!f_exten || ft_strncmp(f_exten, ".cub", 5))
		return (cub_errno(WRITE, EREXT), 1);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (cub_errno(WRITE, ERNOFILE), cub_errinfo(path), 1);
	tex_init(scene);
	if (fd < 0
		|| get_textures(fd, scene)
		|| get_map(fd, scene))
		return (1);
	printf("If you want a job done well hire a professional!\n");
	return (close(fd), 0);
}

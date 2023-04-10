/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 17:28:00 by pharbst           #+#    #+#             */
/*   Updated: 2023/04/10 03:15:01 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_error.h"

static int	validate_texture(char *line, t_scene *scene)
{
	if (!ft_strncmp(line, "NO", 2))
		scene->map.fd_no = open(skip_space(line + 2), O_RDONLY);
	else if (!ft_strncmp(line, "SO", 2))
		scene->map.fd_so = open(skip_space(line + 2), O_RDONLY);
	else if (!ft_strncmp(line, "WE", 2))
		scene->map.fd_we = open(skip_space(line + 2), O_RDONLY);
	else if (!ft_strncmp(line, "EA", 2))
		scene->map.fd_ea = open(skip_space(line + 2), O_RDONLY);
	else
		return (cub_errno(WRITE, ERNOID), 1);
	if (scene->map.fd_no < 0 || scene->map.fd_so < 0
		|| scene->map.fd_we < 0 || scene->map.fd_ea < 0)
		return (cub_errno(WRITE, ERNOFILE), 1);
	return (0);
}

int	get_textures(int fd, t_scene *scene)
{
	char	*line;
	char	*tmp;

	while (scene->map.fd_no == 0 || scene->map.fd_so == 0
		|| scene->map.fd_we == 0 || scene->map.fd_ea == 0)
	{
		line = get_next_line(fd);
		if (!line)
			return (clean_pars(scene), 1);
		tmp = skip_space(line);
		if (*tmp != '\0' && validate_texture(tmp, scene))
			return (free(line), clean_pars(scene), 1);
		free(line);
	}
	return (0);
}

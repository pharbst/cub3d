/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 17:28:00 by pharbst           #+#    #+#             */
/*   Updated: 2023/04/04 18:46:48 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_error.h"

int	validate_texture(char *line, t_scene *scene)
{
	if (!ft_strcmp(line, "NO"))
		scene->map.fd_no = open(skip_space(line + 2), O_RDONLY);
	else if (!ft_strcmp(line, "SO"))
		scene->map.fd_so = open(skip_space(line + 2), O_RDONLY);
	else if (!ft_strcmp(line, "WE"))
		scene->map.fd_we = open(skip_space(line + 2), O_RDONLY);
	else if (!ft_strcmp(line, "EA"))
		scene->map.fd_ea = open(skip_space(line + 2), O_RDONLY);
	else
		return (cub_errno(WRITE, ERNOID), cub_strerror(), 1);
	if (scene->map.fd_no < 0 || scene->map.fd_so < 0
		|| scene->map.fd_we < 0 || scene->map.fd_ea < 0)
		return (ft_putstr_fd(), 1);
}

int	get_cf_colors(int fd, t_scene *scene)
{
	
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
	get_cf_colors(fd, scene);
	return (0);
}

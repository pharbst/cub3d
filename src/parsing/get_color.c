/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 18:56:56 by pharbst           #+#    #+#             */
/*   Updated: 2023/04/05 19:04:24 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_error.h"

static int	get_f_color(char *rgb, t_scene *scene)
{
	char	**split;

	split = ft_split(rgb, ',');
	if (!split || !split[0] || !split[1] || !split[2] || split[3])
		return (cub_errno(WRITE, ERFORMAT), 1);
	scene->map.color_floor = ft_atoi(split[0]) << 16;
	scene->map.color_floor += ft_atoi(split[1]) << 8;
	scene->map.color_floor += ft_atoi(split[2]);
	if (scene->map.color_floor < 0 || scene->map.color_floor > 0xFFFFFF)
		return (cub_errno(WRITE, ERFORMAT), 1);
	return (0);
}

static int	get_c_color(char *rgb, t_scene *scene)
{
	char	**split;

	split = ft_split(rgb, ',');
	if (!split || !split[0] || !split[1] || !split[2] || split[3])
		return (cub_errno(WRITE, ERFORMAT), 1);
	scene->map.color_ceiling = ft_atoi(split[0]) << 16;
	scene->map.color_ceiling += ft_atoi(split[1]) << 8;
	scene->map.color_ceiling += ft_atoi(split[2]);
	if (scene->map.color_ceiling < 0 || scene->map.color_ceiling > 0xFFFFFF)
		return (cub_errno(WRITE, ERFORMAT), 1);
	return (0);
}

static int	convert_color(char *tmp, t_scene *scene)
{
	int		i;

	if (tmp && *tmp == 'F')
		i = get_f_color(tmp + 1, scene);
	else if (tmp && *tmp == 'C')
		i = get_c_color(tmp + 1, scene);
	else
		return (cub_errno(WRITE, ERNOID), 1);
	if (i)
		return (cub_errno(WRITE, ERFORMAT), 1);
	return (0);
}

int	get_cf_colors(int fd, t_scene *scene)
{
	char	*line;
	char	*tmp;

	scene->map.color_ceiling = -1;
	scene->map.color_floor = -1;
	while (scene->map.color_ceiling == -1 || scene->map.color_floor == -1)
	{
		line = get_next_line(fd);
		if (!line)
			return (clean_pars(scene), cub_errno(WRITE, EREOF), 1);
		tmp = skip_space(line);
		if (*tmp != '\0' && convert_color(tmp, scene))
			return (free(line), clean_pars(scene),
				cub_errno(WRITE, ERFORMAT), 1);
		free(line);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 17:28:00 by pharbst           #+#    #+#             */
/*   Updated: 2023/04/21 14:39:45 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_error.h"

static int	load_texture(char *path, mlx_texture_t **texture)
{
	*texture = mlx_load_png(path);
	if (*texture == NULL)
		return (file_error(path), 1);
	return (0);
}

static int	pars_get_color(char *line, int *color)
{
	int		i;
	int		rgb[3];

	i = 0;
	while (i < 3)
	{
		rgb[i] = ft_atoi(line);
		if (rgb[i] < 0 || rgb[i] > 255)
			return (cub_errno(WRITE, ERFORMAT), 1);
		line = skip_number(line);
		if (i < 2 && *line != ',')
			return (cub_errno(WRITE, ERFORMAT), 1);
		line++;
		i++;
	}
	*color = rgb[0] << 16 | rgb[1] << 8 | rgb[2];
	return (0);
}

static int	validate_texture(char *line, t_scene *scene)
{
	char			*tmp;
	mlx_texture_t	**texture;
	int				*color;

	tmp = line;
	color = NULL;
	if (!ft_strncmp(line, "NO", 2))
		texture = &scene->tex.t_north;
	else if (!ft_strncmp(line, "SO", 2))
		texture = &scene->tex.t_south;
	else if (!ft_strncmp(line, "WE", 2))
		texture = &scene->tex.t_west;
	else if (!ft_strncmp(line, "EA", 2))
		texture = &scene->tex.t_east;
	else if (!ft_strncmp(line, "F", 1))
		color = &scene->tex.floor;
	else if (!ft_strncmp(line, "C", 1))
		color = &scene->tex.ceiling;
	else
		return (texture_error(tmp));
	if (!color)
		return (load_texture(skip_space(line + 2), texture));
	return (pars_get_color(skip_space(line + 1), color));
}

int	get_textures(int fd, t_scene *scene)
{
	char	*line;
	char	*tmp;

	while (scene->tex.t_north == NULL || scene->tex.t_south == NULL
		|| scene->tex.t_west == NULL || scene->tex.t_east == NULL
		|| scene->tex.floor == -1 || scene->tex.ceiling == -1)
	{
		line = get_next_line(fd);
		if (!line)
			return (close(fd), cub_errno(WRITE, EREOF), 1);
		tmp = ft_strtrim(line, "\n");
		free(line);
		line = tmp;
		tmp = skip_space(line);
		if (*tmp != '\0' && validate_texture(tmp, scene))
			return (free(line), close(fd), 1);
		free(line);
	}
	printf("textures loaded!!\n");
	return (0);
}

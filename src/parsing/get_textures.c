/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 17:28:00 by pharbst           #+#    #+#             */
/*   Updated: 2023/04/25 14:41:57 by pharbst          ###   ########.fr       */
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

static int	pars_get_color(char *line, t_pixel *color)
{
	int		i;
	int		rgb[3];

	i = 0;
	while (i < 3)
	{
		rgb[i] = ft_atoi(line);
		if (rgb[i] > 255)
			return (cub_errno(WRITE, ERFORMAT), 1);
		line = skip_number(line);
		if (i < 2 && *line != ',')
			return (cub_errno(WRITE, ERFORMAT), 1);
		line++;
		i++;
	}
	color->a = 0XFF;
	color->r = rgb[0];
	printf("r: %x\n", color->r);
	color->g = rgb[1];
	printf("g: %x\n", color->g);
	color->b = rgb[2];
	printf("b: %x\n", color->b);
	return (0);
	// printf("rgb: %x %x %x\n", rgb[0], rgb[1], rgb[2]);
	// return (color->a = 0XFF, color->r = rgb[0],
	// 	color->g = rgb[1], color->b = rgb[2], 0);
}

static int	validate_texture(char *line, t_scene *scene)
{
	char			*tmp;
	mlx_texture_t	**texture;
	t_pixel			*color;

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
		|| scene->tex.floor.pixel == 0 || scene->tex.ceiling.pixel == 0)
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
	printf("t_north: %p\nt_south: %p\nt_west: %p\nt_east: %p\nfloor: %x\nceiling: %x\n", scene->tex.t_north, scene->tex.t_south, scene->tex.t_west, scene->tex.t_east, scene->tex.floor.pixel, scene->tex.ceiling.pixel);
	return (0);
}

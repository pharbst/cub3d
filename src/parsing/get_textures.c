/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlohmann <jlohmann@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 17:28:00 by pharbst           #+#    #+#             */
/*   Updated: 2023/05/03 02:04:24 by jlohmann         ###   ########.fr       */
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

static int	get_color(char *line, t_color *color)
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
	return (color->a = 0XFF, color->r = rgb[0],
		color->g = rgb[1], color->b = rgb[2], 0);
}

static int	validate_texture(char *line, t_tex *tex)
{
	char			*tmp;
	mlx_texture_t	**texture;
	t_color			*color;

	tmp = line;
	color = NULL;
	if (!ft_strncmp(line, "NO", 2))
		texture = &tex->t_north;
	else if (!ft_strncmp(line, "SO", 2))
		texture = &tex->t_south;
	else if (!ft_strncmp(line, "WE", 2))
		texture = &tex->t_west;
	else if (!ft_strncmp(line, "EA", 2))
		texture = &tex->t_east;
	else if (!ft_strncmp(line, "F", 1))
		color = &tex->floor;
	else if (!ft_strncmp(line, "C", 1))
		color = &tex->ceiling;
	else
		return (texture_error(tmp));
	if (!color)
		return (load_texture(skip_space(line + 2), texture));
	return (get_color(skip_space(line + 1), color));
}

int	get_textures(int fd, t_tex *tex)
{
	char	*line;
	char	*tmp;

	while (tex->t_north == NULL || tex->t_south == NULL
		|| tex->t_west == NULL || tex->t_east == NULL
		|| tex->floor.pixel == 0 || tex->ceiling.pixel == 0)
	{
		line = get_next_line(fd);
		if (!line)
			return (close(fd), cub_errno(WRITE, EREOF), 1);
		tmp = ft_strtrim(line, "\n");
		free(line);
		line = tmp;
		tmp = skip_space(line);
		if (*tmp != '\0' && validate_texture(tmp, tex))
			return (free(line), close(fd), 1);
		free(line);
	}
	return (0);
}

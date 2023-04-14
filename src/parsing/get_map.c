/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 19:05:35 by pharbst           #+#    #+#             */
/*   Updated: 2023/04/14 02:04:21 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_error.h"

static char	*go_to_start(int fd)
{
	char	*line;

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			return (cub_errno(WRITE, EREOF), line);
		if (ft_strlen(line) > 0 && *skip_space(line) != '\0')
			break ;
		free(line);
	}
	return (line);
}

static char	**read_map(int fd, char *line, t_scene *scene)
{
	char	**map;
	char	**tmp;

	map = NULL;
	scene->map.height = 0;
	while (line && *skip_space(line) != '\0')
	{
		line = cub_trim(line);
		scene->map.height++;
		tmp = ft_calloc(scene->map.height + 1, sizeof(char *));
		if (!tmp)
			return (cub_errno(WRITE, ERALLOC), ft_free_split(tmp), NULL);
		if (map)
			ft_memcpy(tmp, map, (scene->map.height) * sizeof(char *));
		tmp[scene->map.height - 1] = line;
		map = tmp;
		line = get_next_line(fd);
	}
	if (line)
		free(line);
	return (map);
}

int	get_map(int fd, t_scene *scene)
{
	char	*line;
	char	**map;

	line = go_to_start(fd);
	if (!line)
		return (1);
	map = read_map(fd, line, scene);
	if (!map || parse_map(map))
		return (1);
	if (check_map(map, scene))
		return (1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlohmann <jlohmann@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 19:05:35 by pharbst           #+#    #+#             */
/*   Updated: 2023/05/03 02:13:37 by jlohmann         ###   ########.fr       */
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
			return (cub_errno(WRITE, ERALLOC), ft_free_split(map), NULL);
		if (map)
		{
			ft_memcpy(tmp, map, (scene->map.height) * sizeof(char *));
			free(map);
		}
		tmp[scene->map.height - 1] = line;
		map = tmp;
		line = get_next_line(fd);
	}
	if (line)
		free(line);
	return (map);
}

static int	expand_tab(char **map, int i, int *j)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_substr(map[i], 0, *j);
	tmp2 = ft_strjoin(tmp, "0000");
	free(tmp);
	tmp = ft_strjoin(tmp2, map[i] + *j + 1);
	free(map[i]);
	map[i] = tmp;
	*j += 3;
	return (0);
}

static int	parse_map(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (' ' == map[i][j])
				map[i][j] = '0';
			else if ('\t' == map[i][j])
				expand_tab(map, i, &j);
			else if (!ft_strchr("01NSWE", map[i][j]))
				return (cub_errno(WRITE, ERFORMAT), 1);
			j++;
		}
		i++;
	}
	return (0);
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

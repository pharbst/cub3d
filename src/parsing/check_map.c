/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 01:49:55 by pharbst           #+#    #+#             */
/*   Updated: 2023/04/10 02:57:05 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_error.h"

static char	*convert_map(char **map, t_scene *scene)
{
	char	*ret_map;
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (map[++i])
		if ((int)ft_strlen(map[i]) > j)
			j = ft_strlen(map[i]);
	ret_map = ft_calloc(j * scene->map.height, sizeof(char));
	if (!ret_map)
		return (cub_errno(WRITE, ERALLOC), NULL);
	i = -1;
	while (map[++i])
	{
		ft_memcpy(ret_map + (i * j), map[i], ft_strlen(map[i]));
		if ((int)ft_strlen(map[i]) < j)
			ft_memset(ret_map + (i * j) + ft_strlen(map[i]),
				'0', j - ft_strlen(map[i]));
		free(map[i]);
	}
	free(map);
	return (ret_map);
}

char	*check_map(char **map, t_scene *scene)
{
	printf("map check not implemented yet\n");
	return (convert_map(map, scene));
}

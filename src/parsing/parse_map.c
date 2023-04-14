/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 01:46:43 by pharbst           #+#    #+#             */
/*   Updated: 2023/04/14 02:19:48 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int	parse_map(char **map)
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

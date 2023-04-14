/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 17:28:40 by pharbst           #+#    #+#             */
/*   Updated: 2023/04/14 00:30:22 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*skip_space(char *line)
{
	if (!line)
		return (NULL);
	while (ft_iswhitespace(*line) && *line)
		line++;
	return (line);
}

char	*first_word(char *line)
{
	int		i;

	i = 0;
	while (line[i] && !ft_iswhitespace(line[i]))
		i++;
	return (ft_substr(line, 0, i));
}

char	*skip_number(char *line)
{
	if (!line)
		return (NULL);
	while (*line && ft_iswhitespace(*line))
		line++;
	while (*line && (ft_isdigit(*line)))
		line++;
	return (line);
}

char	*cub_trim(char *line)
{
	char	*tmp;

	tmp = line;
	line = ft_strtrim(line, "\n");
	free(tmp);
	return (line);
}

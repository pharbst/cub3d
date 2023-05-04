/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlohmann <jlohmann@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 17:28:40 by pharbst           #+#    #+#             */
/*   Updated: 2023/05/04 16:48:54 by jlohmann         ###   ########.fr       */
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

// this function deletes whitespaces at the end of the line
void	map_trim(char *line)
{
	int	i;

	i = ft_strlen(line) - 1;
	while (i >= 0 && ft_iswhitespace(line[i]))
	{
		line[i] = '\0';
		i--;
	}
}

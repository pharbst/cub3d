/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlohmann <jlohmann@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 05:50:17 by pharbst           #+#    #+#             */
/*   Updated: 2023/04/27 20:46:10 by jlohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_map(t_scene *scene)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	printf("Map:\n   ");
	while (i < scene->map.width)
		printf("%2d|", i++);
	i = 0;
	printf("\n");
	while (i < scene->map.height)
	{
		j = 0;
		printf("%2d|", i);
		while (j < scene->map.width)
		{
			printf("%2c|", scene->map.data[i * scene->map.width + j]);
			j++;
		}
		i++;
		printf("\n");
	}
}

void	print_player(t_scene *scene)
{
	printf("Player:\n");
	printf("   pos: (%f, %f)\n", scene->player.pos.x, scene->player.pos.y);
	printf("   dir: (%f, %f)\n", scene->player.dir.x, scene->player.dir.y);
	printf("   plane: (%f, %f)\n", scene->player.plane.x, scene->player.plane.y);
}

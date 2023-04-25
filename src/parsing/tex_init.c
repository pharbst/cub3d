/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 22:16:48 by pharbst           #+#    #+#             */
/*   Updated: 2023/04/25 13:26:44 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	tex_init(t_scene *scene)
{
	scene->tex.ceiling.pixel = 0;
	scene->tex.floor.pixel = 0;
	scene->tex.t_east = NULL;
	scene->tex.t_north = NULL;
	scene->tex.t_south = NULL;
	scene->tex.t_west = NULL;
	return (0);
}

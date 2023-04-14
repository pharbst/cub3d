/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 22:16:48 by pharbst           #+#    #+#             */
/*   Updated: 2023/04/13 22:28:00 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	tex_init(t_scene *scene)
{
	scene->tex.ceiling = -1;
	scene->tex.floor = -1;
	scene->tex.t_east = NULL;
	scene->tex.t_north = NULL;
	scene->tex.t_south = NULL;
	scene->tex.t_west = NULL;
	return (0);
}

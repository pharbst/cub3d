/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_pars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 18:42:04 by pharbst           #+#    #+#             */
/*   Updated: 2023/04/05 18:42:31 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clean_pars(t_scene *scene)
{
	if (scene->map.fd_no > 0)
		close(scene->map.fd_no);
	if (scene->map.fd_so > 0)
		close(scene->map.fd_so);
	if (scene->map.fd_we > 0)
		close(scene->map.fd_we);
	if (scene->map.fd_ea > 0)
		close(scene->map.fd_ea);
}

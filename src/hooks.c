/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlohmann <jlohmann@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 12:21:58 by jlohmann          #+#    #+#             */
/*   Updated: 2023/03/31 14:11:42 by jlohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	update(void *param)
{
	t_scene		*scene;

	scene = (t_scene *)param;
	if (mlx_is_key_down(scene->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(scene->mlx);
	player_draw(&scene->player);
}

// updates 60 times per second
void	fixed_update(void *param)
{
	static double	last_time = 0.0;
	double			current_time;
	double			frame_time;
	t_scene			*scene;
	
	scene = (t_scene *)param;
	// TODO: verify, if this works
	current_time = mlx_get_time();
	frame_time = (current_time - last_time);
	last_time = current_time;
	player_update(scene->mlx, &scene->player, frame_time * 60.0);
}

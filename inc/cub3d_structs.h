/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_structs.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 13:12:38 by pharbst           #+#    #+#             */
/*   Updated: 2023/04/25 17:03:34 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_STRUCTS_H
# define CUB3D_STRUCTS_H

# include "MLX42/MLX42.h"
# include "graphics.h"
# include <stdbool.h>

// --- Game object structs --- //

typedef union s_pixel
{
	struct
	{
		unsigned char	r;
		unsigned char	g;
		unsigned char	b;
		unsigned char	a;
	};
	uint32_t	pixel;
}	t_pixel;

typedef struct s_player {
	t_vec		pos;
	t_vec		dir;
	t_vec		plane;
	mlx_image_t	*img;
	double		fov;
}	t_player;

typedef struct s_map {
	uint16_t	width;
	uint16_t	height;
	char		*data;
	mlx_image_t	*img;
}	t_map;

typedef struct s_tex {
	mlx_texture_t	*t_north;
	mlx_texture_t	*t_south;
	mlx_texture_t	*t_west;
	mlx_texture_t	*t_east;
	t_pixel			floor;
	t_pixel			ceiling;
}	t_tex;

typedef struct s_scene {
	mlx_t		*mlx;
	mlx_image_t	*background;
	mlx_image_t	*screen;
	mlx_image_t	*fps_screen;
	t_map		map;
	t_tex		tex;
	t_player	player;
}	t_scene;

// --- Helper structs --- //

typedef struct s_keystate {
	bool	w;
	bool	a;
	bool	s;
	bool	d;
	bool	left;
	bool	right;
	bool	shift;
}	t_keystate;

typedef struct s_dda_params {
	double	camera_x;
	t_vec	ray_dir;
	t_point	block_pos;
	t_point	step_dir;
	t_vec	dist;
	t_vec	delta;
}	t_dda_params;

typedef struct s_hit_info {
	double	dist;
	t_vec	pos;
	t_point	block_pos;
	int		side;
}	t_hit_info;

#endif

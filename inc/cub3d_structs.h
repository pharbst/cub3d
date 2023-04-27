/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_structs.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlohmann <jlohmann@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 13:12:38 by pharbst           #+#    #+#             */
/*   Updated: 2023/04/27 21:59:41 by jlohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_STRUCTS_H
# define CUB3D_STRUCTS_H

# include "MLX42/MLX42.h"

// --- Geometric structs --- //

typedef struct s_point {
	int32_t	x;
	int32_t	y;
}	t_point;

typedef struct s_vec {
	double	x;
	double	y;
}	t_vec;

typedef struct s_rect {
	int32_t	x;
	int32_t	y;
	int32_t	width;
	int32_t	height;
}	t_rect;

// --- Game object structs --- //

typedef union s_color
{
	uint32_t	pixel;
	struct
	{
		uint8_t	r;
		uint8_t	g;
		uint8_t	b;
		uint8_t	a;
	};
}	t_color;

typedef struct s_player {
	t_vec		pos;
	t_vec		dir;
	t_vec		plane;
	mlx_image_t	*img;
	double		fov;
}	t_player;

typedef struct s_map {
	uint16_t		width;
	uint16_t		height;
	char			*data;
	mlx_image_t		*img;
	mlx_texture_t	*pixbuf;
}	t_map;

typedef struct s_tex {
	mlx_texture_t	*t_north;
	mlx_texture_t	*t_south;
	mlx_texture_t	*t_west;
	mlx_texture_t	*t_east;
	t_color			floor;
	t_color			ceiling;
}	t_tex;

typedef struct s_scene {
	mlx_t		*mlx;
	mlx_image_t	*background;
	mlx_image_t	*screen;
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
	bool	alt;
}	t_keystate;

typedef struct s_dda_params {
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

typedef struct s_tex_params {
	mlx_texture_t	*tex;
	t_vec			pos;
	double			step;
}	t_tex_params;

#endif

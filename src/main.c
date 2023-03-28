#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "MLX42/MLX42.h"

#define WIDTH 1024
#define HEIGHT 512

// Exit the program as failure.
static void ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

// Print the window width and height.
/*static void ft_hook(void* param)
{
	const mlx_t* mlx = param;

	printf("WIDTH: %d | HEIGHT: %d\n", mlx->width, mlx->height);
}*/

void input_func(mlx_key_data_t keydata, void *param)
{
	mlx_image_t *player;

	player = (mlx_image_t *)param;
	if (keydata.key == MLX_KEY_UP && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		player->instances[0].y -= 5;
	if (keydata.key == MLX_KEY_RIGHT && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		player->instances[0].x += 5;
	if (keydata.key == MLX_KEY_DOWN && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		player->instances[0].y += 5;	
	if (keydata.key == MLX_KEY_LEFT && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		player->instances[0].x -= 5;
}

void	fill_color(mlx_image_t *img, uint32_t color)
{
	for (uint32_t y=0; y<img->height; y++)
	{
		for (uint32_t x=0; x<img->width; x++)
			mlx_put_pixel(img, x, y, color);
	}
}

int32_t	main(void)
{
	//uint32_t player_x, player_y;
	// MLX allows you to define its core behaviour before startup.
	//mlx_set_setting(MLX_MAXIMIZED, true);
	mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "Raycast Experiments", true);
	if (!mlx)
		ft_error();

	// Background
	mlx_image_t* img = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
		ft_error();
	fill_color(img, 0x000000FF);

	// Player
	//player_x = 30; player_y = 30;
	mlx_image_t *player_img = mlx_new_image(mlx, 8, 8);
	if (!player_img || (mlx_image_to_window(mlx, player_img, 300, 300) < 0))
		ft_error();
	fill_color(player_img, 0xFFFF00FF);
	// Register a hook and pass mlx as an optional param.
	// NOTE: Do this before calling mlx_loop!
	// mlx_loop_hook(mlx, ft_hook, mlx);
	mlx_key_hook(mlx, input_func, player_img);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlohmann <jlohmann@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 20:25:11 by jlohmann          #+#    #+#             */
/*   Updated: 2023/04/01 21:16:32 by jlohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* void	print_help(void)
{
	ft_putstr_fd("\nUSAGE:\n   ./cub3D path/to/scene.cub\n", STDERR_FILENO);
	ft_putstr_fd("EXAMPLE:\n   ./cub3D ./scenes/example.cub\n", STDERR_FILENO);
	ft_putstr_fd("CONTROLS:\n", STDERR_FILENO);
	ft_putstr_fd(" * [W, A, S, D]   move player\n", STDERR_FILENO);
	ft_putstr_fd(" * [ARROW KEYS]   move view\n", STDERR_FILENO);
	ft_putstr_fd(" * [ESC]          exit\n", STDERR_FILENO);
} */

void	panic(const char *msg)
{
	// TODO: Implement proper cleanup and error handling routine
	printf("%s\n", msg);
	exit(EXIT_FAILURE);
}

void	mlx_panic(void)
{
	// TODO: Implement proper cleanup and error handling routine
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

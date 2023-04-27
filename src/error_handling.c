/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlohmann <jlohmann@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 20:25:11 by jlohmann          #+#    #+#             */
/*   Updated: 2023/04/27 20:15:22 by jlohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

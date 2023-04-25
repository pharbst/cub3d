/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:28:57 by pharbst           #+#    #+#             */
/*   Updated: 2023/04/25 16:42:30 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FPS_H
# define FPS_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_fps
{
	uint64_t	prev_t;
	uint64_t	prev_s;
	uint64_t	fps_log[120];
	uint32_t		i;
	uint64_t	t;
	uint64_t	t_delta;
	uint16_t	fps_delta;
}	t_fps;

// returns every 1/5 second the ø fps of all previous function calls
// otherwise it returns -1
int	fps_counter(void);

#endif
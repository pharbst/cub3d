/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps_counter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 15:52:14 by pharbst           #+#    #+#             */
/*   Updated: 2023/04/26 21:52:58 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fps.h"
#include <stdio.h>

static unsigned long	utime(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000000 + tv.tv_usec);
}

static uint16_t	get_delta(uint64_t *fps_log, uint32_t i)
{
	uint64_t	sum;
	uint32_t	j;

	sum = 0;
	j = 0;
	while (j < i)
	{
		sum += fps_log[j];
		j++;
	}
	return (sum / i);
}

int	fps_counter(void)
{
	static t_fps	data;

	data.t = utime();
	if (!data.prev_t || !data.prev_s)
	{
		data.prev_t = data.t;
		data.prev_s = data.t;
		return (-1);
	}
	data.t_delta = data.t - data.prev_t;
	data.fps_log[data.i] = 1000000 / data.t_delta;
	data.i++;
	if (data.prev_s + 200000 < data.t)
	{
		data.prev_s = data.t;
		data.fps_delta = get_delta(data.fps_log, data.i);
		printf("fps: %d\n", data.fps_delta);
		return (data.fps_delta);
	}
	data.prev_t = data.t;
	return (-1);
}

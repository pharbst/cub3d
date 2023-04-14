/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 01:49:55 by pharbst           #+#    #+#             */
/*   Updated: 2023/04/14 02:19:06 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_error.h"

int	add_queue(t_list **queue, int coords[2])
{
	t_list	*tmp;

	tmp = ft_lstnew(create_vector(coords[0] + 1, coords[1]));
	if (!tmp)
		return (1);
	ft_lstadd_back(queue, tmp);
	tmp = ft_lstnew(create_vector(coords[0] - 1, coords[1]));
	if (!tmp)
		return (1);
	ft_lstadd_back(queue, tmp);
	tmp = ft_lstnew(create_vector(coords[0], coords[1] + 1));
	if (!tmp)
		return (1);
	ft_lstadd_back(queue, tmp);
	tmp = ft_lstnew(create_vector(coords[0], coords[1] - 1));
	if (!tmp)
		return (1);
	ft_lstadd_back(queue, tmp);
	return (0);
}

int	check_algo(t_scene *scene, t_list **queue, char old)
{
	t_list	*tmp;
	int		coords[2];

	coords[0] = ((int *)((*queue)->content))[0];
	coords[1] = ((int *)((*queue)->content))[1];
	if (coords[0] < 0 || coords[1] < 0
		|| coords[0] >= scene->map.width
		|| coords[1] >= scene->map.height)
		return (ft_lstclear(queue, &free), cub_errno(WRITE, ERMAP), 1);
	if (scene->map.data[coords[0] + coords[1] * scene->map.width] == '1'
		|| scene->map.data[coords[0] + coords[1] * scene->map.width] == '0')
		return (tmp = (*queue)->next, ft_lstdelone(*queue, &free), *queue = tmp,
			0);
	if (scene->map.data[coords[0] + coords[1] * scene->map.width] == old)
	{
		scene->map.data[coords[0] + coords[1] * scene->map.width] = '0';
		tmp = (*queue)->next;
		ft_lstdelone(*queue, &free);
		*queue = tmp;
		if (add_queue(queue, coords))
			return (cub_errno(WRITE, ERALLOC), 1);
	}
	return (0);
}

int	check_main(t_scene *scene)
{
	int		coords[2];
	char	old;
	t_list	*queue;

	old = '.';
	if (find_start(coords, scene))
		return (1);
	scene->map.data = ft_strreplace(scene->map.data, '0', old);
	scene->map.data[coords[0] + coords[1] * scene->map.width] = '0';
	queue = ft_lstnew(create_vector(coords[0] + 1, coords[1]));
	ft_lstadd_back(&queue, ft_lstnew(create_vector(coords[0] - 1, coords[1])));
	ft_lstadd_back(&queue, ft_lstnew(create_vector(coords[0], coords[1] + 1)));
	ft_lstadd_back(&queue, ft_lstnew(create_vector(coords[0], coords[1] - 1)));
	while (queue)
	{
		if (check_algo(scene, &queue, old))
			return (1);
	}
	scene->map.data = ft_strreplace(scene->map.data, old, '0');
	return (0);
}

int	check_map(char **map, t_scene *scene)
{
	scene->map.data = convert_map(map, scene);
	if (!scene->map.data)
		return (1);
	if (check_main(scene))
		return (1);
	return (0);
}

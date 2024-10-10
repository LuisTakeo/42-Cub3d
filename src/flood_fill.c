/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phraranha <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 22:51:19 by phraranha         #+#    #+#             */
/*   Updated: 2024/10/10 22:51:27 by phraranha        ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static bool	floodfill(t_scene *scene, bool **filled_map, int i, int j)
{
	bool	is_surrounded;

	if (i < 0 || i >= scene->map.map_height || j < 0
		|| j >= scene->map.map_width)
		return (false);
	if (scene->map.map_data[i][j] == '1' || filled_map[i][j] == true)
		return (true);
	else
		filled_map[i][j] = true;
	is_surrounded = true;
	is_surrounded &= floodfill(scene, filled_map, i - 1, j);
	is_surrounded &= floodfill(scene, filled_map, i + 1, j);
	is_surrounded &= floodfill(scene, filled_map, i, j - 1);
	is_surrounded &= floodfill(scene, filled_map, i, j + 1);
	return (is_surrounded);
}

int	check_map_surrounded(t_scene *scene, t_pos pos)
{
	int		x;
	int		y;
	int		i;
	bool	**filled_map;
	bool	is_surrounded;

	x = pos.x;
	y = pos.y;
	filled_map = ft_calloc(scene->map.map_height + 1, sizeof(bool *));
	i = 0;
	while (i < scene->map.map_height)
	{
		filled_map[i] = ft_calloc(scene->map.map_width, sizeof(bool));
		if (!filled_map[i])
		{
			free_line_array((char **)filled_map, scene->map.map_height);
			err_exit("malloc failed");
		}
		i++;
	}
	is_surrounded = floodfill(scene, filled_map, y, x);
	free_line_array((char **)filled_map, scene->map.map_height);
	if (!is_surrounded)
		panic("not surrounded", scene);
	return (0);
}


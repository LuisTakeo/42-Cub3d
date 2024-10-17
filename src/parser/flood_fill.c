/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaim-yu <tpaim-yu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 22:51:19 by phraranha         #+#    #+#             */
/*   Updated: 2024/10/17 01:27:39 by tpaim-yu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	print_flood_filled_map(t_scene *scene, bool **filled_map)
{
	int	i;
	int	j;

	i = 0;
	while (i < scene->map.map_height)
	{
		j = 0;
		while (j < scene->map.map_width)
		{
			if (filled_map[i][j])
				ft_putchar_fd('#', 2);
			else
				ft_putchar_fd(scene->map.map_data[i][j], 2);
			j++;
		}
		ft_putchar_fd('\n', 2);
		i++;
	}
}

static bool	floodfill(t_scene *scene, bool **filled_map, int i, int j)
{
	bool	is_surrounded;

	if (i < 0 || i >= scene->map.map_height || j < 0
		|| j >= scene->map.map_width)
		return (false);
	if (scene->map.map_data[i][j] == ' ' || scene->map.map_data[i][j] == '\t'
		|| scene->map.map_data[i][j] == '2')
		return (false);
	if (scene->map.map_data[i][j] == '1' || filled_map[i][j] == true)
		return (true);
	filled_map[i][j] = true;
	is_surrounded = true;
	is_surrounded &= floodfill(scene, filled_map, i - 1, j);
	is_surrounded &= floodfill(scene, filled_map, i + 1, j);
	is_surrounded &= floodfill(scene, filled_map, i, j - 1);
	is_surrounded &= floodfill(scene, filled_map, i, j + 1);
	return (is_surrounded);
}

bool	**allocate_filled_map(t_scene *scene)
{
	bool	**filled_map;
	int		i;

	filled_map = ft_calloc(scene->map.map_height, sizeof(bool *));
	if (!filled_map)
		err_exit("Memory allocation failed for filled_map");
	i = 0;
	while (i < scene->map.map_height)
	{
		filled_map[i] = ft_calloc(scene->map.map_width, sizeof(bool));
		if (!filled_map[i])
		{
			free_line_array((char **)filled_map, i);
			err_exit("Memory allocation failed for filled_map row");
		}
		i++;
	}
	return (filled_map);
}

void	validate_player_position(t_scene *scene, t_pos pos)
{
	if (scene->map.map_data[pos.y][pos.x] != 'N'
		&& scene->map.map_data[pos.y][pos.x] != 'W'
		&& scene->map.map_data[pos.y][pos.x] != 'E'
		&& scene->map.map_data[pos.y][pos.x] != 'S')
		panic("Player position is not in a walkable area", scene);
}

int	check_map_surrounded(t_scene *scene, t_pos pos)
{
	bool	**filled_map;
	bool	is_surrounded;

	filled_map = allocate_filled_map(scene);
	validate_player_position(scene, pos);
	is_surrounded = floodfill(scene, filled_map, pos.y, pos.x);
	free_line_array((char **)filled_map, scene->map.map_height);
	if (!is_surrounded)
		panic("Map is not surrounded by walls", scene);
	return (0);
}

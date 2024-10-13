/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phraranha <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 22:51:19 by phraranha         #+#    #+#             */
/*   Updated: 2024/10/13 17:17:48 by phraranha        ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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

	printf("Visiting cell (%d, %d)\n", i, j);
	print_flood_filled_map(scene, filled_map);
	if (i < 0 || i >= scene->map.map_height || j < 0
		|| j >= scene->map.map_width)
	{
		printf("Out of bounds at (%d, %d)\n", i, j);
		return (false);
	}
	if (scene->map.map_data[i][j] == ' ' || scene->map.map_data[i][j] == '\t')
	{
		printf("space tab");
		return (false);
	}
	if (scene->map.map_data[i][j] == '1' || filled_map[i][j] == true)
	{
		printf("Hit a wall or visited at (%d, %d)\n", i, j);
		return (true);
	}
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
	int		i;
	bool	**filled_map;
	bool	is_surrounded;

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
	if (scene->map.map_data[pos.y][pos.x] != 'N'
		&& scene->map.map_data[pos.y][pos.x] != 'W'
		&& scene->map.map_data[pos.y][pos.x] != 'E'
		&& scene->map.map_data[pos.y][pos.x] != 'S')
	{
		free_line_array((char **)filled_map, scene->map.map_height);
		panic("Player position is not in a walkable area", scene);
	}
	is_surrounded = floodfill(scene, filled_map, pos.y, pos.x);
	free_line_array((char **)filled_map, scene->map.map_height);
	if (!is_surrounded)
		panic("Map is not surrounded by walls", scene);
	return (0);
}

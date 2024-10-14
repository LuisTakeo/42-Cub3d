/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phraranha <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 22:51:19 by phraranha         #+#    #+#             */
/*   Updated: 2024/10/14 16:22:21 by paranha          ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
void	print_map(char **map_data, int map_height, int map_width)
{
	int	i;

	i = 0;
	printf("Map (Height: %d, Width: %d):\n", map_height, map_width);
	while (i < map_height)
	{
		printf("%s\n", map_data[i]);
		i++;
	}
}

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
	//print_flood_filled_map( scene, filled_map);

	if (i < 0 || i >= scene->map.map_height || j < 0
		|| j >= scene->map.map_width)
	{
		printf("Out of bounds at (%d, %d)\n", i, j);
		return (false);
	}
	if (scene->map.map_data[i][j] == ' ' || scene->map.map_data[i][j] == '\t' || scene->map.map_data[i][j] == '2')
	{
		printf("space tab");
		return (false);
	}
	if (scene->map.map_data[i][j] == '1' || filled_map[i][j] == true)
	{
		//printf("Hit a wall or visited at (%d, %d)\n", i, j);
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
	print_map(scene->map.map_data, scene->map.map_height, scene->map.map_width);
	return (0);
}

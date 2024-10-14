/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phraranha <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 22:52:48 by phraranha         #+#    #+#             */
/*   Updated: 2024/10/14 16:10:36 by paranha          ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

bool	handle_map_line(char *line, bool *map_started)
{
	if (is_map_line(&line[0]))
	{
		*map_started = true;
	}
	else if (!is_map_line(line) && *map_started)
	{
		err("Stopped parsing at non-map line after map started.");
		return (false);
	}
	return (true);
}

void	parse_map_from_lines(char **lines, int line_count, t_scene *scene,
		t_pos *player_pos)
{
	char	*line;
	int		i;

	init_map_vars(*scene);
	i = 0;
	scene->map.map_data = NULL;
	while (i < line_count)
	{
		line = lines[i];
		if (!handle_map_line(line, &scene->map_started))
			break ;
		if (scene->map_started)
		{
			calculate_map_width(line, &scene->map.map_width);
			resize_map_data(scene, scene->map.map_height);
			copy_map_line(scene, line, scene->map.map_height);
			validate_map_characters(line, ft_strlen(line), scene, player_pos);
			scene->map.map_height++;
		}
		i++;
	}
	final_map_validation(scene);
}

bool	count_elements_from_lines(char **lines, int line_count, t_scene *scene)
{
	bool	map_started;
	int		i;
	char	*line;

	map_started = false;
	i = 0;
	while (i < line_count && !map_started)
	{
		line = lines[i];
		if (is_whitespace(*line))
		{
			i++;
			continue ;
		}
		if (is_map_line(line))
			map_started = true;
		else
			count_texture_elements(line, scene);
		i++;
	}
	if (scene->no_counter != 1 || scene->so_counter != 1
		|| scene->we_counter != 1 || scene->ea_counter != 1
		|| scene->f_counter != 1 || scene->c_counter != 1)
		return (err("Missing or repeated elements"), false);
	return (true);
}

void	adjust_line_length(t_scene *scene, int i, int max_width)
{
	int		current_length;
	char	*temp_line;

	current_length = ft_strlen(scene->map.map_data[i]);
	if (current_length > 0 && scene->map.map_data[i][current_length
		- 1] == '\n')
	{
		scene->map.map_data[i][current_length - 1] = '\0';
		current_length--;
	}
	if (current_length < max_width)
	{
		temp_line = malloc(max_width + 1);
		if (!temp_line)
			err_exit("Memory allocation failed");
		ft_strlcpy(temp_line, scene->map.map_data[i], current_length + 1);
		ft_memset(temp_line + current_length, '2', max_width - current_length);
		temp_line[max_width] = '\0';
		free(scene->map.map_data[i]);
		scene->map.map_data[i] = temp_line;
	}
}

void	fill_map_with_zeros(t_scene *scene)
{
	int	i;
	int	max_width;

	i = 0;
	max_width = scene->map.map_width;
	while (i < scene->map.map_height)
	{
		adjust_line_length(scene, i, max_width);
		i++;
	}
	// scene->map.map_data[scene->map.map_height] = NULL;
}
char	**convert_to_split(t_scene *scene)
{
	char	*map_string;
	char	**split_map;
	int		total_length;
	int		i;

	total_length = 0;
	i = 0;
	while (i < scene->map.map_height)
	{
		total_length += ft_strlen(scene->map.map_data[i]) + 1;
		i++;
	}
	map_string = malloc(total_length + 1);
	if (!map_string)
		err_exit("Memory allocation failed for map_string");
	map_string[0] = '\0';
	i = 0;
	while (i < scene->map.map_height)
	{
		ft_strlcat(map_string, scene->map.map_data[i], total_length + 1);
		ft_strlcat(map_string, "\n", total_length + 1);
		i++;
	}
	split_map = ft_split(map_string, '\n');
	free(map_string);
	return (split_map);
}

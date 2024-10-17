/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaim-yu <tpaim-yu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 22:52:48 by phraranha         #+#    #+#             */
/*   Updated: 2024/10/17 17:35:48 by phraranha        ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	process_element_line(char *line, t_scene *scene, char **lines,
		int line_count)
{
	if (is_valid_element_line(line))
		count_texture_elements(line, scene);
	else
	{
		err("Invalid line in scene configuration");
		free_line_array(lines, line_count);
		exit(EXIT_FAILURE);
	}
}

bool	validate_element_counters(t_scene *scene)
{
	if (scene->no_counter != 1 || scene->so_counter != 1
		|| scene->we_counter != 1 || scene->ea_counter != 1
		|| scene->f_counter != 1 || scene->c_counter != 1)
	{
		err("Missing or repeated elements");
		return (false);
	}
	return (true);
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
		if (is_empty_line(line))
			i++;
		else if (is_map_line(line))
			map_started = true;
		else
		{
			process_element_line(line, scene, lines, line_count);
			i++;
		}
	}
	return (validate_element_counters(scene));
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

void	fill_map_with_twos(t_scene *scene)
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
}

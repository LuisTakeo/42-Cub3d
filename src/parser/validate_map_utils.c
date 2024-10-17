/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaim-yu <tpaim-yu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 01:42:01 by tpaim-yu          #+#    #+#             */
/*   Updated: 2024/10/17 17:58:16 by paranha          ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

bool	is_empty_line(char *line)
{
	while (*line)
	{
		if (!is_whitespace(*line))
			return (false);
		line++;
	}
	return (true);
}

bool	handle_map_line(char *line, bool *map_started)
{
	if (is_map_line(&line[0]))
		*map_started = true;
	else if (!is_map_line(line) && *map_started)
		return (false);
	return (true);
}

bool	non_map_line(char *line, bool *map_started)
{
	if (is_map_line(&line[0]))
		*map_started = true;
	else if (!is_empty_line(line) && is_map_line(line) && *map_started)
		return (false);
	else if (!is_empty_line(line) && !is_map_line(line) && *map_started)
		return (false);
	return (true);
}

void	verify_lines(char **lines, int line_count, int i, t_scene *scene)
{
	char	*line;

	while (i < line_count)
	{
		line = lines[i];
		if (!non_map_line(line, &scene->map_started))
			panic_exit("garbage after the map", scene);
		i++;
	}
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
	verify_lines(lines, line_count, i, scene);
	final_map_validation(scene);
}

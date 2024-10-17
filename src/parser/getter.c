/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phraranha <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 23:20:52 by phraranha         #+#    #+#             */
/*   Updated: 2024/10/16 20:19:58 by phraranha        ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

t_direction	get_direction(char *identifier)
{
	if (ft_strncmp(identifier, "NO", 2) == 0)
		return (NORTH);
	if (ft_strncmp(identifier, "SO", 2) == 0)
		return (SOUTH);
	if (ft_strncmp(identifier, "WE", 2) == 0)
		return (WEST);
	if (ft_strncmp(identifier, "EA", 2) == 0)
		return (EAST);
	return (INVALID_DIRECTION);
}

char	**read_file_lines(int fd, t_scene *scene)
{
	char	**lines;
	char	*line;
	int		count;

	count = 0;
	lines = NULL;
	line = get_next_line(fd);
	while (line != NULL)
	{
		lines = ft_realloc(lines, sizeof(char *) * count, sizeof(char *)
				* (count + 1));
		if (!lines)
			err_exit("Memory allocation failed");
		lines[count] = ft_strdup(line);
		if (!lines[count])
			err_exit("Memory allocation failed");
		count++;
		free(line);
		if (line != NULL)
			line = get_next_line(fd);
	}
	scene->line_count = count;
	return (lines);
}

void	count_texture_elements(char *line, t_scene *scene)
{
	t_direction	dir;

	dir = get_direction(line);
	if (dir == NORTH)
		scene->no_counter++;
	else if (dir == SOUTH)
		scene->so_counter++;
	else if (dir == WEST)
		scene->we_counter++;
	else if (dir == EAST)
		scene->ea_counter++;
	else if (*line == 'F')
		scene->f_counter++;
	else if (*line == 'C')
		scene->c_counter++;
}

void	parse_scene_from_lines(char **lines, int line_count, t_scene *scene)
{
	int			i;
	char		*line;
	t_direction	dir;

	i = 0;
	while (i < line_count)
	{
		line = lines[i];
		dir = get_direction(line);
		if (dir != INVALID_DIRECTION)
			handle_texture(scene, dir, line);
		else if (*line == 'F')
			handle_floor_color(scene, line);
		else if (*line == 'C')
			handle_ceiling_color(scene, line);
		i++;
	}
}

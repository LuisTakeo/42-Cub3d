/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freerror.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaim-yu <tpaim-yu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 22:45:15 by phraranha         #+#    #+#             */
/*   Updated: 2024/10/17 01:49:21 by tpaim-yu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	free_components(char **components)
{
	int	i;

	i = 0;
	while (components[i])
	{
		free(components[i]);
		i++;
	}
	free(components);
}

void	free_line_array(char **lines, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(lines[i]);
		i++;
	}
	free(lines);
}

void	free_map_data(char **map_data, int height)
{
	int	i;

	i = 0;
	if (map_data)
	{
		while (i < height)
		{
			if (map_data[i])
			{
				free(map_data[i]);
				map_data[i] = NULL;
			}
			i++;
		}
	}
}

void	panic_exit(char *error_message, t_scene *scene)
{
	err(error_message);
	free_map_data(scene->map.map_data, scene->map.map_height);
	free_line_array(scene->file_lines, scene->line_count);
	free(scene->map.map_data);
	free(scene->north_texture);
	free(scene->south_texture);
	free(scene->west_texture);
	free(scene->east_texture);
	exit(EXIT_FAILURE);
}

void	panic(char *err_msg, t_scene *scene)
{
	err(err_msg);
	if (scene->map.map_data)
		free_map_data(scene->map.map_data, scene->map.map_height);
	if (scene->file_lines)
		free_line_array(scene->file_lines, scene->line_count);
	free(scene->map.map_data);
	free(scene->north_texture);
	free(scene->south_texture);
	free(scene->west_texture);
	free(scene->east_texture);
	exit(EXIT_FAILURE);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaim-yu <tpaim-yu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 01:34:31 by tpaim-yu          #+#    #+#             */
/*   Updated: 2024/10/17 01:34:31 by tpaim-yu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

bool	is_valid_map_char(char c)
{
	return (c == '1' || c == '0' || c == ' ' || c == '\t' || c == '\n');
}

bool	is_player_char(char c)
{
	return (c == 'N' || c == 'W' || c == 'E' || c == 'S');
}

void	calculate_map_width(char *line, int *map_width)
{
	int	current_width;

	current_width = ft_strlen(line);
	while (current_width > 0 && is_whitespace(line[current_width - 1]))
		current_width--;
	if (current_width > *map_width)
		*map_width = current_width;
}

void	resize_map_data(t_scene *scene, int map_height)
{
	scene->map.map_data = ft_realloc(scene->map.map_data, sizeof(char *)
			* map_height, sizeof(char *) * (map_height + 1));
	if (!scene->map.map_data)
	{
		err("Memory allocation failed");
		exit(EXIT_FAILURE);
	}
}

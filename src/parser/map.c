/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaim-yu <tpaim-yu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 22:52:12 by phraranha         #+#    #+#             */
/*   Updated: 2024/10/17 18:57:30 by paranha          ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	copy_map_line(t_scene *scene, char *line, int map_height)
{
	scene->map.map_data[map_height] = ft_strdup(line);
	if (!scene->map.map_data[map_height])
	{
		err("Memory allocation failed");
		exit(EXIT_FAILURE);
	}
}

void	validate_map_characters(char *line, int current_width, t_scene *scene,
		t_pos *player_pos)
{
	int		j;
	char	c;

	j = 0;
	while (j < current_width)
	{
		c = line[j];
		if (is_player_char(c))
		{
			scene->player_count++;
			player_pos->x = j;
			player_pos->y = scene->map.map_height;
		}
		else if (!is_valid_map_char(c))
			scene->invalid_c++;
		j++;
	}
}

void	final_map_validation(t_scene *scene)
{
	if (scene->player_count != 1)
		panic("This is not a multiplayer game, nor a non player game", scene);
	if (scene->invalid_c > 0)
		panic("Invalid characters in map", scene);
	if (scene->map.map_width > 100)
		panic("too thicc", scene);
	if (scene->map.map_height > 100)
		panic("too tall", scene);
}

void	init_map_vars(t_scene scene)
{
	scene.map.map_height = 0;
	scene.map.map_width = 0;
	scene.player_count = 0;
	scene.map_started = false;
	scene.invalid_c = 0;
}

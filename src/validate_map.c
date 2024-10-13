/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phraranha <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 22:52:48 by phraranha         #+#    #+#             */
/*   Updated: 2024/10/13 16:19:00 by phraranha        ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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

// void	fill_map_with_zeros(t_scene *scene)
//{
//	int		max_width;
//	int		i;
//	int		current_length;
//	char	*new_line;
//
//	i = 0;
//	max_width = scene->map.map_width;
//	while (i < scene->map.map_height)
//	{
//		current_length = ft_strlen(scene->map.map_data[i]);
//		if (current_length < max_width)
//		{
//			new_line = malloc(max_width + 1);
//			if (!new_line)
//				err_exit("Memory allocation failed");
//			while(current_length < max_width)
//				ft_memset(new_line, '0', max_width);
//			new_line[max_width] = '\0';
//			free(scene->map.map_data[i]);
//			scene->map.map_data[i] = new_line;
//		}
//		i++;
//	}
//}

void	fill_map_with_zeros(t_scene *scene)
{
	int		i;
	int		current_length;
	int		max_width;
	char	*temp_line;

	i = 0;
	max_width = scene->map.map_width;
	while (i < scene->map.map_height)
	{
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
			ft_memset(temp_line + current_length, '0', max_width
				- current_length);
			temp_line[max_width] = '\0';
			free(scene->map.map_data[i]);
			scene->map.map_data[i] = temp_line;
		}
		i++;
	}
}

// void	fill_map_with_zeros(t_scene *scene)
//{
//	int		i;
//	int		current_length;
//	int		max_width;
//	char	*temp_line;
//
//	i = 0;
//	max_width = scene->map.map_width;
//
//	// Iterate through each line of the map.
//	while (i < scene->map.map_height)
//	{
//		current_length = ft_strlen(scene->map.map_data[i]);
//
//		// Only proceed if the current line is shorter than the maximum width.
//		if (current_length < max_width)
//		{
//			// Allocate a temporary buffer with max_width
//			temp_line = malloc(max_width + 1);
//			if (!temp_line)
//				err_exit("Memory allocation failed");
//
//			// Copy the original line into the temporary buffer.
//			ft_strlcpy(temp_line, scene->map.map_data[i], current_length + 1);
//
//			// Fill the rest of the buffer with '0' characters.
//			ft_memset(temp_line + current_length, '0', max_width
//
//			// Add the null-terminator at the end.
//			temp_line[max_width] = '\0';
//
//			// Free the original line and replace it with the newly filled line.
//			free(scene->map.map_data[i]);
//			scene->map.map_data[i] = temp_line;
//		}
//
//		i++;
//	}
//}
//
// void	fill_short_lines_with_zeros(t_scene *scene)
//{
//	int		max_width;
//	int		i;
//	int		current_length;
//
//	i = 0;
//	max_width = scene->map.map_width;
//	while (i < scene->map.map_height)
//	{
//		current_length = ft_strlen(scene->map.map_data[i]);
//		if (current_length < max_width)
//		{
//			// Reallocate memory for the current line to accommodate max_width characters.
//			scene->map.map_data[i] = realloc(scene->map.map_data[i], max_width
//			if (!scene->map.map_data[i])
//				err_exit("Memory allocation failed");
//
//			// Fill the remaining portion with '0's.
//			while (current_length < max_width)
//			{
//				scene->map.map_data[i][current_length] = '0';
//				current_length++;
//			}
//
//			// Null terminate the string.
//			scene->map.map_data[i][max_width] = '\0';
//		}
//		i++;
//	}
//}

// void	fill_short_lines_with_zeros(t_scene *scene)
//{
//	int		max_width;
//	int		i;
//	int		current_length;
//	char	*new_line;
//
//	i = 0;
//	max_width = scene->map.map_width;
//	while (i < scene->map.map_height)
//	{
//		current_length = ft_strlen(scene->map.map_data[i]);
//		if (current_length < max_width)
//		{
//			// Allocate new memory for the line with the size of max_width
//			new_line = malloc(max_width + 1);
//			if (!new_line)
//				err_exit("Memory allocation failed");
//
//			// Copy the original string into the new allocated memory.
//			ft_memcpy(new_line, scene->map.map_data[i], current_length);
//
//			// Fill the rest of the line with '0'.
//			ft_memset(new_line + current_length, '0', max_width
//
//			// Null-terminate the new string.
//			new_line[max_width] = '\0';
//
//			// Free the old line and assign the new one.
//			free(scene->map.map_data[i]);
//			scene->map.map_data[i] = new_line;
//		}
//		i++;
//	}
//}

// void	fill_short_lines_with_zeros(t_scene *scene)
//{
//	int		max_width;
//	int		i;
//	int		current_length;
//
//	i = 0;
//	max_width = scene->map.map_width;
//	while (i < scene->map.map_height)
//	{
//		current_length = ft_strlen(scene->map.map_data[i]);
//		if (current_length < max_width)
//		{
//			// Allocate enough memory for the line with 'max_width' length
//			scene->map.map_data[i] = realloc(scene->map.map_data[i], max_width
//			if (!scene->map.map_data[i])
//				err_exit("Memory allocation failed");
//
//			// Fill the rest of the line with '0' from the end of the current string to max_width.
//			ft_memset(scene->map.map_data[i] + current_length, '0', max_width
//
//			// Null-terminate the new string.
//			scene->map.map_data[i][max_width] = '\0';
//		}
//		i++;
//	}
//}

// void	fill_map_with_zeros(t_scene *scene)
//{
//	int		i;
//	int		j;
//	int		max_width;
//	int		current_length;
//	char	**new_map;
//
//	i = 0;
//	max_width = scene->map.map_width;
//
//	// Allocate memory for the new map with the proper dimensions.
//	new_map = malloc(sizeof(char *) * (scene->map.map_height + 1));
//	if (!new_map)
//		err_exit("Memory allocation failed");
//
//	// Copy each line, filling with '0' as necessary.
//	while (i < scene->map.map_height)
//	{
//		current_length = ft_strlen(scene->map.map_data[i]);
//		new_map[i] = malloc(max_width + 1); // Allocate memory for each new row.
//		if (!new_map[i])
//			err_exit("Memory allocation failed");
//
//		// Copy over the original data.
//		j = 0;
//		while (j < current_length)
//		{
//			new_map[i][j] = scene->map.map_data[i][j];
//			j++;
//		}
//
//		// Fill the rest of the line with '0'.
//		while (j < max_width)
//		{
//			new_map[i][j] = '0';
//			j++;
//		}
//
//		new_map[i][max_width] = '\0'; // Null-terminate each row.
//		i++;
//	}
//
//	new_map[scene->map.map_height] = NULL; // Null-terminate the map array.
//
//	// Free the old map.
//	i = 0;
//	while (scene->map.map_data[i])
//	{
//		free(scene->map.map_data[i]);
//		i++;
//	}
//	free(scene->map.map_data);
//
//	// Assign the new map to the scene.
//	scene->map.map_data = new_map;
//}
//

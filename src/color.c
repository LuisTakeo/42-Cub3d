/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phraranha <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 22:50:09 by phraranha         #+#    #+#             */
/*   Updated: 2024/10/13 17:37:47 by phraranha        ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_valid_color_value(int value)
{
	return (value >= 0 && value <= 255);
}

bool	validate_color_components(char **components)
{
	if (!components[0] || !components[1] || !components[2])
	{
		err("Invalid color format");
		free_components(components);
		return (false);
	}
	if (ft_strlen(components[0]) > 3 || ft_strlen(components[1]) > 3
		|| ft_strlen(components[2]) > 3)
	{
		err("Error: Invalid color format (length)");
		free_components(components);
		return (false);
	}
	return (true);
}

void	handle_floor_color(t_scene *scene, char *line)
{
	char	*temp;

	temp = ft_strchr(line, ' ');
	if (temp)
	{
		temp++;
		while (is_whitespace(*temp))
			temp++;
		temp = ft_strtrim(temp, "\n ' ' '\t'");
		if (!temp)
		{
			free(line);
			scene->floor_color = -1;
			return ;
		}
		scene->floor_color = parse_color(temp);
		if (scene->floor_color == EXIT_FAILURE)
		{
			free(temp);
			scene->floor_color = -1;
			return ;
		}
	}
	free(temp);
}

void	handle_ceiling_color(t_scene *scene, char *line)
{
	char	*temp;

	temp = ft_strchr(line, ' ');
	if (temp)
	{
		temp++;
		while (is_whitespace(*temp))
			temp++;
		temp = ft_strtrim(temp, "\n ' ' '\t'");
		if (!temp)
		{
			free(line);
			scene->ceiling_color = -1;
			return ;
		}
		scene->ceiling_color = parse_color(temp);
		if (scene->ceiling_color == EXIT_FAILURE)
		{
			free(temp);
			scene->ceiling_color = -1;
			return ;
		}
	}
	free(temp);
}

int	rgb_to_hex(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

void	hex_to_rgb(int hex, int *r, int *g, int *b)
{
	*r = (hex >> 16) & 0xFF;
	*g = (hex >> 8) & 0xFF;
	*b = hex & 0xFF;
}

int	parse_color(char *line)
{
	char	**components;
	int		r;
	int		g;
	int		b;

	components = ft_split(line, ',');
	if (!components)
		return (err("ft_split"), EXIT_FAILURE);
	if (!validate_color_components(components))
		return (EXIT_FAILURE);
	r = ft_atoi(components[0]);
	g = ft_atoi(components[1]);
	b = ft_atoi(components[2]);
	free_components(components);
	if (!is_valid_color_value(r) || !is_valid_color_value(g)
		|| !is_valid_color_value(b))
		return (err("Error: Color values must be between 0 and 255"),
			EXIT_FAILURE);
	return ((r << 16) | (g << 8) | b);
}

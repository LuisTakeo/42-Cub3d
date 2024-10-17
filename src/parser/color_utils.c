/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaim-yu <tpaim-yu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 01:38:21 by tpaim-yu          #+#    #+#             */
/*   Updated: 2024/10/17 17:58:29 by paranha          ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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
		err("Invalid color format (length)");
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
			scene->floor_color = -2;
			return ;
		}
		scene->floor_color = parse_color(temp);
		if (scene->floor_color == -2)
		{
			free(temp);
			scene->floor_color = -2;
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
			scene->ceiling_color = -2;
			return ;
		}
		scene->ceiling_color = parse_color(temp);
		if (scene->ceiling_color == -2)
		{
			free(temp);
			scene->ceiling_color = -2;
			return ;
		}
	}
	free(temp);
}

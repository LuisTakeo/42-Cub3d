/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phraranha <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 23:22:18 by phraranha         #+#    #+#             */
/*   Updated: 2024/10/10 23:35:48 by phraranha        ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	handle_texture(t_scene *scene, t_direction dir, char *line)
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
			return ;
		}
		if (dir == NORTH)
			scene->north_texture = ft_strdup(temp);
		else if (dir == SOUTH)
			scene->south_texture = ft_strdup(temp);
		else if (dir == WEST)
			scene->west_texture = ft_strdup(temp);
		else if (dir == EAST)
			scene->east_texture = ft_strdup(temp);
		free(temp);
	}
}

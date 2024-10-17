/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phraranha <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 22:48:42 by phraranha         #+#    #+#             */
/*   Updated: 2024/10/10 22:50:00 by phraranha        ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	*ft_realloc(void *ptr, size_t original_size, size_t new_size)
{
	void	*new;

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	else if (!ptr)
		return (malloc(new_size));
	else if (new_size <= original_size)
		return (ptr);
	else
	{
		new = malloc(new_size);
		if (!new)
		{
			free(ptr);
			return (NULL);
		}
		ft_memcpy(new, ptr, original_size);
		free(ptr);
		return (new);
	}
}

bool	is_whitespace(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (true);
	else
		return (false);
}

bool	is_map_line(char *line)
{
	return (ft_isdigit(*line) || *line == SPACE || *line == TAB);
}

bool	handle_line(char *line, t_scene *scene, bool *map_started)
{
	if (is_whitespace(*line))
		return (false);
	if (is_map_line(line))
	{
		*map_started = true;
		return (false);
	}
	count_texture_elements(line, scene);
	return (true);
}

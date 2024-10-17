/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaim-yu <tpaim-yu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 00:40:33 by tpaim-yu          #+#    #+#             */
/*   Updated: 2024/10/17 00:40:33 by tpaim-yu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

char	**push_map(t_map *map)
{
	char	**new_map;
	int		i;

	new_map = ft_calloc(map->map_height + 1, sizeof(char *));
	if (!new_map)
		err_exit("Memory allocation failed for new_map");
	i = 0;
	while (i < map->map_height)
	{
		new_map[i] = ft_strdup(map->map_data[i]);
		if (!new_map[i])
		{
			free_map(new_map);
			err_exit("Memory allocation failed for new_map row");
		}
		i++;
	}
	return (new_map);
}

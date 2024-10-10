/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaim-yu <tpaim-yu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 21:58:37 by tpaim-yu          #+#    #+#             */
/*   Updated: 2024/09/11 21:58:37 by tpaim-yu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/../includes/cub3d.h"

void	free_map(char **map)
{
	int32_t	i;

	i = -1;
	while (map[++i])
		free(map[i]);
	free(map);
	map = NULL;
}

void	finish_game(t_cub3d *cub3d)
{
	if (cub3d->mlx)
		mlx_terminate(cub3d->mlx);
	if (cub3d->map)
		free_map(cub3d->map);
}


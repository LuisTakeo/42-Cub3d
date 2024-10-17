/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaim-yu <tpaim-yu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 22:33:18 by tpaim-yu          #+#    #+#             */
/*   Updated: 2024/10/16 22:33:18 by tpaim-yu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	ft_array_size(char **array)
{
	int	i;

	i = 0;
	while (array && array[i])
		i++;
	return (i);
}

t_vector	filter_size(char **map, t_vector pos)
{
	t_vector	size;

	size = pos;
	if (pos.y < 0)
		size.y = 0;
	else if (pos.y > ft_array_size(map))
		size.y = ft_array_size(map) - 1;
	if (pos.x < 0)
		size.x = 0;
	else if (pos.x > ft_strlen(map[(int)pos.y]))
		size.x = ft_strlen(map[(int)pos.y]) - 1;
	return (size);
}

void	compare_and_calculate_x_and_y(t_cub3d *cub3d, t_vector *dda_line_size,
	t_vector *wall_map_pos)
{
	if (dda_line_size->x < dda_line_size->y)
	{
		dda_line_size->x += cub3d->player.delta_dist.x;
		wall_map_pos->x += cub3d->player.step.x;
		cub3d->player.side = 0;
	}
	else
	{
		dda_line_size->y += cub3d->player.delta_dist.y;
		wall_map_pos->y += cub3d->player.step.y;
		cub3d->player.side = 1;
	}
}

float	calculate_return_of_dda(t_cub3d *cub3d, t_vector ray_dir,
	t_vector wall_map_pos)
{
	if (!cub3d->player.side)
		return (((wall_map_pos.x - cub3d->player.pos.x / TILE_SIZE)
				+ (1 - cub3d->player.step.x) / 2) / ray_dir.x);
	else
		return (((wall_map_pos.y - cub3d->player.pos.y / TILE_SIZE)
				+ (1 - cub3d->player.step.y) / 2) / ray_dir.y);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaim-yu <tpaim-yu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 17:45:40 by tpaim-yu          #+#    #+#             */
/*   Updated: 2024/10/13 17:45:40 by tpaim-yu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

float	calculate_return_of_dda(t_cub3d *cub3d, t_vector ray_dir, t_vector wall_map_pos)
{
	if (!cub3d->player.side)
		return (((wall_map_pos.x - cub3d->player.pos.x / TILE_SIZE)
				+ (1 - cub3d->player.step.x) / 2) / ray_dir.x);
	else
		return (((wall_map_pos.y - cub3d->player.pos.y / TILE_SIZE)
				+ (1 - cub3d->player.step.y) / 2) / ray_dir.y);
}

int			ft_array_size(char **array)
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

float	calculate_dda(t_cub3d *cub3d, t_vector ray_dir)
{
	t_vector	dda_line_size;
	t_vector	wall_map_pos;

	(void)ray_dir;
	update_vector(&wall_map_pos, cub3d->player.map_pos.x,
		cub3d->player.map_pos.y);
	update_vector(&dda_line_size, cub3d->player.dist_to_side.x,
		cub3d->player.dist_to_side.y);
	while (ft_strchr("0NEWS",
			cub3d->map[(int)wall_map_pos.y][(int)wall_map_pos.x]))
	{
		if (dda_line_size.x < dda_line_size.y)
		{
			dda_line_size.x += cub3d->player.delta_dist.x;
			wall_map_pos.x += cub3d->player.step.x;
			cub3d->player.side = 0;
		}
		else
		{
			dda_line_size.y += cub3d->player.delta_dist.y;
			wall_map_pos.y += cub3d->player.step.y;
			cub3d->player.side = 1;
		}
		wall_map_pos = filter_size(cub3d->map, wall_map_pos);
	}
	if (!cub3d->player.side)
		return (((wall_map_pos.x - cub3d->player.pos.x / TILE_SIZE)
				+ (1 - cub3d->player.step.x) / 2) / ray_dir.x);
	else
		return (((wall_map_pos.y - cub3d->player.pos.y / TILE_SIZE)
				+ (1 - cub3d->player.step.y) / 2) / ray_dir.y);
}

t_vector	find_ray_dir(t_cub3d *cub3d, int x)
{
	float		multiplier;
	t_vector	camera_pixel;

	multiplier = 2 * x / (float)WIDTH - 1;
	camera_pixel = multi_vector(cub3d->player.camera_plane, multiplier);
	return (sum_vector(cub3d->player.dir, camera_pixel));
}



t_vector	calculate_delta_dist(t_vector ray_dir)
{
	t_vector	delta_dist;

	if (ray_dir.x == 0)
		delta_dist.x = HUGE_VALF;
	else
		delta_dist.x = fabsf(1 / ray_dir.x);
	if (ray_dir.y == 0)
		delta_dist.y = HUGE_VALF;
	else
		delta_dist.y = fabsf(1 / ray_dir.y);
	return (delta_dist);
}

void	calculate_dist_to_side(t_cub3d *cub3d, t_vector ray_dir)
{
	if (ray_dir.x < 0)
		cub3d->player.dist_to_side.x = ((cub3d->player.pos.x / TILE_SIZE)
				- cub3d->player.map_pos.x) * cub3d->player.delta_dist.x;
	else
		cub3d->player.dist_to_side.x = (cub3d->player.map_pos.x + 1.0f
				- (cub3d->player.pos.x / TILE_SIZE))
			* cub3d->player.delta_dist.x;
	if (ray_dir.y < 0)
		cub3d->player.dist_to_side.y = ((cub3d->player.pos.y / TILE_SIZE)
				- cub3d->player.map_pos.y) * cub3d->player.delta_dist.y;
	else
		cub3d->player.dist_to_side.y = (cub3d->player.map_pos.y + 1.0f
				- (cub3d->player.pos.y / TILE_SIZE))
			* cub3d->player.delta_dist.y;
}
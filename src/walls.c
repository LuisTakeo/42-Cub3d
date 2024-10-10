/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaim-yu <tpaim-yu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 20:02:05 by tpaim-yu          #+#    #+#             */
/*   Updated: 2024/10/09 20:02:05 by tpaim-yu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_vector	find_ray_dir(t_cub3d *cub3d, int x)
{
	float		multiplier;
	t_vector	camera_pixel;

	multiplier = 2 * (x / (float)WIDTH) - 1;
	camera_pixel = multi_vector(cub3d->player.cameraPlane, multiplier);
	return (sum_vector(cub3d->player.dir, camera_pixel));
}



t_vector	calculate_delta_dist(t_vector ray_dir)
{
	t_vector	delta_dist;

	if (ray_dir.x == 0)
		update_vector(&delta_dist, 1, 0);
	else if (ray_dir.y == 0)
		delta_dist.x = 0;
	else
		delta_dist.x = fabs(1 / ray_dir.x);
	if (ray_dir.y == 0)
		update_vector(&delta_dist, 0, 1);
	else if (ray_dir.x == 0)
		delta_dist.y = 0;
	else
		delta_dist.y = fabs(1 / ray_dir.y);
	return (delta_dist);
}

void	draw_walls(t_cub3d *cub3d)
{
	int			i;
	t_vector	ray_dir;

	(void)cub3d;
	i = 0;
	while (i < WIDTH)
	{
		ray_dir = find_ray_dir(cub3d, i);
		cub3d->player.delta_dist = calculate_delta_dist(ray_dir);
		printf("Delta dist: x = %f, y = %f\n", cub3d->player.delta_dist.x, cub3d->player.delta_dist.y);
		i++;
	}
}

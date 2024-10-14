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

#include "../../includes/cub3d.h"

void	set_direction(t_cub3d *cub3d, t_vector ray)
{
	if (ray.x < 0)
		cub3d->player.step.x = -1;
	else
		cub3d->player.step.x = 1;
	if (ray.y < 0)
		cub3d->player.step.y = -1;
	else
		cub3d->player.step.y = 1;
}



void	draw_wall_line(t_cub3d *cub3d, float perp_wall_dist, int x)
{
	int		wall_line_height;
	int		draw_start;
	int		draw_end;
	int		color;

	wall_line_height = (int)(HEIGHT / perp_wall_dist);
	draw_start = HEIGHT / 2 - wall_line_height / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = HEIGHT / 2 + wall_line_height / 2;
	if (draw_end >= HEIGHT)
		draw_end = HEIGHT - 1;
	if (!cub3d->player.side)
	{
		if (cub3d->player.step.x == -1)
			color = 0xFF0000FF;
		else
			color = 0xFFFFAAFF;
	}
	else
	{
		if (cub3d->player.step.y == -1)
			color = 0x00FF00FF;
		else
			color = 0x0000FFFF;
	}
	draw_vertical_line(cub3d->image, (t_vector){x, draw_start},
		draw_end, color);
}

void	draw_walls(t_cub3d *cub3d)
{
	int			i;
	float		perp_wall_dist;
	t_vector	ray_dir;

	i = 0;
	while (i < WIDTH)
	{
		ray_dir = find_ray_dir(cub3d, i);
		set_direction(cub3d, ray_dir);

		cub3d->player.delta_dist = calculate_delta_dist(ray_dir);
		update_vector(&cub3d->player.map_pos,
			(int)(cub3d->player.pos.x / TILE_SIZE),
			(int)(cub3d->player.pos.y / TILE_SIZE));
		calculate_dist_to_side(cub3d, ray_dir);
		perp_wall_dist = calculate_dda(cub3d, ray_dir);
		draw_wall_line(cub3d, perp_wall_dist, i);
		i++;
	}
}

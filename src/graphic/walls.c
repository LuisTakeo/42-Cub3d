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

t_vector	find_ray_dir(t_cub3d *cub3d, int x)
{
	float		multiplier;
	t_vector	camera_pixel;

	multiplier = 2 * x / (float)WIDTH - 1;
	camera_pixel = multi_vector(cub3d->player.cameraPlane, multiplier);
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

float	calculate_dda(t_cub3d *cub3d, t_vector ray_dir)
{
	t_vector	dda_line_size;
	t_vector	wall_map_pos;

	(void)ray_dir;
	update_vector(&wall_map_pos, cub3d->player.map_pos.x,
		cub3d->player.map_pos.y);
	update_vector(&dda_line_size, cub3d->player.dist_to_side.x,
		cub3d->player.dist_to_side.y);
	while (cub3d->map[(int)wall_map_pos.y][(int)wall_map_pos.x] != '1')
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
	}
	if (!cub3d->player.side)
		return (((wall_map_pos.x - cub3d->player.pos.x / TILE_SIZE)
				+ (1 - cub3d->player.step.x) / 2) / ray_dir.x);
	else
		return (((wall_map_pos.y - cub3d->player.pos.y / TILE_SIZE)
				+ (1 - cub3d->player.step.y) / 2) / ray_dir.y);
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

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

void	define_wall_size(t_wall *wall, float perp_wall_dist)
{
	wall->wall_height = (HEIGHT / perp_wall_dist);
	if (wall->wall_height <= 0)
		wall->wall_height = 1;
	wall->draw_start = (HEIGHT / 2 - wall->wall_height / 2);
	wall->draw_end = (HEIGHT / 2 + wall->wall_height / 2);
	if (wall->draw_start < 0)
		wall->draw_start = 0;
	if (wall->draw_end >= HEIGHT)
		wall->draw_end = HEIGHT - 1;
}

void	define_wall_point_x(t_wall *wall, t_cub3d *cub3d, t_vector ray_dir,
	float perp_wall_dist)
{
	if (cub3d->player.side == 0)
		wall->wall_point_x = cub3d->player.pos.y + perp_wall_dist * ray_dir.y;
	else
		wall->wall_point_x = cub3d->player.pos.x + perp_wall_dist * ray_dir.x;
	wall->wall_point_x = fmod(wall->wall_point_x, TILE_SIZE) / TILE_SIZE;
}

void	define_wall_tex(t_wall *wall, t_cub3d *cub3d, t_vector ray_dir,
	float perp_wall_dist)
{
	wall->text_x = (int)(wall->wall_point_x * wall->texture->width);
	if (wall->text_x < 0)
		wall->text_x = 0;
	if (wall->text_x >= wall->texture->width)
		wall->text_x = wall->texture->width - 1;
	if (cub3d->player.side == 0)
		wall->wall_point_x = cub3d->player.pos.y + perp_wall_dist * ray_dir.y;
	else
		wall->wall_point_x = cub3d->player.pos.x + perp_wall_dist * ray_dir.x;
	wall->wall_point_x = fmod(wall->wall_point_x, TILE_SIZE) / TILE_SIZE;
	if ((cub3d->player.side == 0 && ray_dir.x < 0)
		|| (cub3d->player.side == 1 && ray_dir.y > 0))
		wall->text_x = wall->texture->width - wall->text_x - 1;
	wall->tex_step = 1.0 * wall->texture->height / wall->wall_height;
	wall->tex_pos = (wall->draw_start - HEIGHT / 2 + wall->wall_height / 2)
		* wall->tex_step;
}

void	draw_wall_line(t_cub3d *cub3d, float perp_wall_dist,
	int x, t_vector ray_dir)
{
	t_wall	wall;

	wall.texture = select_texture(cub3d);
	define_wall_size(&wall, perp_wall_dist);
	define_wall_point_x(&wall, cub3d, ray_dir, perp_wall_dist);
	define_wall_tex(&wall, cub3d, ray_dir, perp_wall_dist);
	draw_line(cub3d, wall, x);
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
		draw_wall_line(cub3d, perp_wall_dist, i, ray_dir);
		i++;
	}
}

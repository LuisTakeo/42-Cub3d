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

mlx_texture_t	*select_texture(t_cub3d *cub3d)
{
	if (!cub3d->player.side)
	{
		if (cub3d->player.step.x == -1)
			return (cub3d->north);
		else
			return (cub3d->south);
	}
	else
	{
		if (cub3d->player.step.y == -1)
			return (cub3d->west);
		else
			return (cub3d->east);
	}
}

uint32_t	get_pixel_color(mlx_texture_t *texture, int x, int y)
{
	int		texture_pos;
	uint8_t	*pixel;

	if (x < 0 || x >= (int)texture->width || y < 0
		|| y >= (int)texture->height)
		return (0);
	texture_pos = y * texture->width + x;
	texture_pos *= texture->bytes_per_pixel;
	pixel = &texture->pixels[texture_pos];
	return (pixel[0] << 24 | pixel[1] << 16 | pixel[2] << 8 | pixel[3]);
}

void	draw_line(t_cub3d *cub3d, t_wall wall, int x)
{
	int			y;
	uint32_t	color;
	int			tex_y;

	y = wall.draw_start;
	while (y < wall.draw_end)
	{
		tex_y = (int)wall.tex_pos;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= (int)wall.texture->height)
			tex_y = wall.texture->height - 1;
		wall.tex_pos += wall.tex_step;
		color = get_pixel_color(wall.texture, wall.text_x, tex_y);
		mlx_put_pixel(cub3d->image, x, y, color);
		y++;
	}
}

void	draw_wall_line(t_cub3d *cub3d, float perp_wall_dist, int x)
{
	t_wall			wall;


	wall.texture = select_texture(cub3d);
	wall.wall_height = (HEIGHT / perp_wall_dist);
	wall.draw_start = (HEIGHT / 2 - wall.wall_height / 2);
	wall.draw_end = (HEIGHT / 2 + wall.wall_height / 2);
	if (wall.draw_start < 0)
		wall.draw_start = 0;
	if (wall.draw_end >= HEIGHT)
		wall.draw_end = HEIGHT - 1;


	if (cub3d->player.side)
		wall.wall_point_x = cub3d->player.pos.x
			+ perp_wall_dist * cub3d->player.delta_dist.x;
	else
		wall.wall_point_x = cub3d->player.pos.y
			+ perp_wall_dist * cub3d->player.delta_dist.y;
	wall.wall_point_x -= floor(wall.wall_point_x);


	wall.text_x = (int)(wall.wall_point_x * wall.texture->width);
	if ((cub3d->player.side == 0 && cub3d->player.dir.x < 0)
		|| (cub3d->player.side == 1 && cub3d->player.dir.y > 0))
		wall.text_x = wall.texture->width - wall.text_x - 1;
	wall.tex_step = 1.0 * wall.texture->height / wall.wall_height;

	wall.tex_pos = (wall.draw_start - HEIGHT / 2 + wall.wall_height / 2)
		* wall.tex_step;
	printf("wall.tex_pos: %f\n", wall.tex_pos);
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
		draw_wall_line(cub3d, perp_wall_dist, i);
		i++;
	}
}

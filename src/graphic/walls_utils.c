/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaim-yu <tpaim-yu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 22:18:50 by tpaim-yu          #+#    #+#             */
/*   Updated: 2024/10/17 17:52:40 by paranha          ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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
		color = get_pixel_color(wall.texture, tex_y, wall.text_x);
		mlx_put_pixel(cub3d->image, x, y, color);
		y++;
	}
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

mlx_texture_t	*select_texture(t_cub3d *cub3d)
{
	if (!cub3d->player.side)
	{
		if (cub3d->player.step.x == -1)
			return (cub3d->west);
		else
			return (cub3d->east);
	}
	else
	{
		if (cub3d->player.step.y == -1)
			return (cub3d->north);
		else
			return (cub3d->south);
	}
}

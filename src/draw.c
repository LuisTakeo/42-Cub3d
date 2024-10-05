/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaim-yu <tpaim-yu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 19:28:55 by tpaim-yu          #+#    #+#             */
/*   Updated: 2024/10/05 19:28:55 by tpaim-yu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	draw_vertical_line(mlx_image_t *image,
	t_vector vector, int y_end, int32_t color)
{
	int y;

	y = vector.y;
	while (y < y_end)
	{
		mlx_put_pixel(image, vector.x, y, color);
		y++;
	}
}

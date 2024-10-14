/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaim-yu <tpaim-yu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 20:47:52 by tpaim-yu          #+#    #+#             */
/*   Updated: 2024/10/13 20:47:52 by tpaim-yu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	identify_move(t_cub3d *cub3d, mlx_key_data_t keydata)
{
	if (keydata.key == MLX_KEY_W)
		moving(cub3d, cub3d->player.dir, 1, 1);
	if (keydata.key == MLX_KEY_S)
		moving(cub3d, cub3d->player.dir, 0, 1);
	if (keydata.key == MLX_KEY_A)
		moving(cub3d, cub3d->player.cameraPlane, 0, 0);
	if (keydata.key == MLX_KEY_D)
		moving(cub3d, cub3d->player.cameraPlane, 1, 0);
	if (keydata.key == MLX_KEY_LEFT)
	{
		cub3d->player.cameraPlane = rotate_vector(cub3d->player.cameraPlane,
				-1.5);
		cub3d->player.dir = rotate_vector(cub3d->player.dir, -1.5);
	}
	if (keydata.key == MLX_KEY_RIGHT)
	{
		cub3d->player.cameraPlane = rotate_vector(cub3d->player.cameraPlane,
				1.5);
		cub3d->player.dir = rotate_vector(cub3d->player.dir, 1.5);
	}
}

void	moving(t_cub3d *cub3d, t_vector dir, int is_positive, int is_x)
{
	t_vector	new_pos;
	float		speed;

	(void)is_x;
	speed = cub3d->mlx->delta_time * 4;
	if (is_positive)
		new_pos = sum_vector(cub3d->player.pos, multi_vector(dir, speed));
	else
		new_pos = sum_vector(cub3d->player.pos, multi_vector(dir, -speed));
	if (verify_margin(cub3d, dir, new_pos, is_x))
		update_vector(&cub3d->player.pos,
			(cub3d->player.pos.x + 1 * (new_pos.x - cub3d->player.pos.x)),
			(cub3d->player.pos.y + 1 * (new_pos.y - cub3d->player.pos.y)));
	printf("x: %f y: %f\n", cub3d->player.pos.x, cub3d->player.pos.y);
}

int	verify_signal(float value)
{
	if (value < 0)
		return (-1);
	return (1);
}

int	verify_margin(t_cub3d *cub3d, t_vector dir, t_vector new_pos, int is_x)
{
	float	margin;

	margin = .2;
	if (is_x && ((cub3d->map[(int)(new_pos.y + margin
					* verify_signal(new_pos.y - cub3d->player.pos.y))]
			[(int)new_pos.x] == '1')
		|| (cub3d->map[(int)(new_pos.y)][(int)(new_pos.x + margin
		* verify_signal(new_pos.x - cub3d->player.pos.x))] == '1')))
		return (0);
	if (!is_x && ((cub3d->map[(int)(new_pos.y + margin
					* verify_signal(dir.y))][(int)new_pos.x] == '1')
				|| (cub3d->map[(int)(new_pos.y)][(int)(new_pos.x + margin
				* verify_signal(dir.x))] == '1')))
		return (0);

	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaim-yu <tpaim-yu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 22:48:06 by tpaim-yu          #+#    #+#             */
/*   Updated: 2024/10/13 22:48:06 by tpaim-yu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ft_hook(void *param)
{
	t_cub3d	*cub3d;

	cub3d = (t_cub3d *)param;
	if (cub3d->is_moving)
	{
		draw_background(cub3d);
		draw_walls(cub3d);
		cub3d->is_moving = 0;
	}
}

void	listen_moves(mlx_key_data_t keydata, void *param)
{
	t_cub3d	*cub3d;

	cub3d = (t_cub3d *)param;
	if (keydata.key == MLX_KEY_ESCAPE)
	{
		finish_game(cub3d);
		exit(EXIT_SUCCESS);
	}
	if (!cub3d->is_moving
		&& (keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_S
			|| keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_D
			|| keydata.key == MLX_KEY_LEFT || keydata.key == MLX_KEY_RIGHT))
	{
		cub3d->is_moving = 1;
		identify_move(cub3d, keydata);
	}
}

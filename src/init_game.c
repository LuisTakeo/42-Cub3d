/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaim-yu <tpaim-yu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 21:58:57 by tpaim-yu          #+#    #+#             */
/*   Updated: 2024/09/11 21:58:57 by tpaim-yu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	listen_moves(mlx_key_data_t keydata, void *param)
{
	t_cub3d	*cub3d;

	cub3d = (t_cub3d *)param;
	if (keydata.key == MLX_KEY_W)
		printf("Walking Front\n");
	if (keydata.key == MLX_KEY_S)
		printf("Walking Back\n");
	if (keydata.key == MLX_KEY_A)
		printf("Walking Left\n");
	if (keydata.key == MLX_KEY_D)
		printf("Walking Right\n");
}

void	init_values(t_cub3d *cub3d)
{
	cub3d->mlx = NULL;
	cub3d->map = NULL;
}

int	init_game(t_cub3d *cub3d)
{
	cub3d->mlx = mlx_init(1280, 800, "Cub3d", true);
	if (!cub3d->mlx)
		return (EXIT_FAILURE);
	mlx_key_hook(cub3d->mlx, &listen_moves, cub3d);
	mlx_loop(cub3d->mlx);
	return (EXIT_SUCCESS);
}
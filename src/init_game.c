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
	mlx_loop(cub3d->mlx);
	return (EXIT_SUCCESS);
}
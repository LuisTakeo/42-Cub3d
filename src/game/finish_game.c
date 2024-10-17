/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaim-yu <tpaim-yu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 21:58:37 by tpaim-yu          #+#    #+#             */
/*   Updated: 2024/10/15 19:02:37 by paranha          ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	free_map(char **map)
{
	int32_t	i;

	i = -1;
	while (map[++i])
		free(map[i]);
	free(map);
	map = NULL;
}

void	free_textures(t_cub3d *cub3d)
{
	if (cub3d->north)
		mlx_delete_texture(cub3d->north);
	if (cub3d->south)
		mlx_delete_texture(cub3d->south);
	if (cub3d->west)
		mlx_delete_texture(cub3d->west);
	if (cub3d->east)
		mlx_delete_texture(cub3d->east);
}

void	finish_game(t_cub3d *cub3d)
{
	if (cub3d->mlx)
		mlx_terminate(cub3d->mlx);
	free_textures(cub3d);
	if (cub3d->map)
		free_map(cub3d->map);
	ok_free("Thanks for playing", &cub3d->scene);
}

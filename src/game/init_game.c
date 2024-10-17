/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaim-yu <tpaim-yu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 21:58:57 by tpaim-yu          #+#    #+#             */
/*   Updated: 2024/10/17 19:18:26 by paranha          ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	init_direction(t_cub3d *cub3d, char direction)
{
	if (direction == 'N')
	{
		update_vector(&cub3d->player.dir, 0, -1);
		update_vector(&cub3d->player.camera_plane, 0.66, 0);
	}
	if (direction == 'S')
	{
		update_vector(&cub3d->player.dir, 0, 1);
		update_vector(&cub3d->player.camera_plane, -0.66, 0);
	}
	if (direction == 'W')
	{
		update_vector(&cub3d->player.dir, -1, 0);
		update_vector(&cub3d->player.camera_plane, 0, -0.66);
	}
	if (direction == 'E')
	{
		update_vector(&cub3d->player.dir, 1, 0);
		update_vector(&cub3d->player.camera_plane, 0, 0.66);
	}
}

void	init_textures(t_cub3d *cub3d)
{
	cub3d->north = mlx_load_png(cub3d->scene.north_texture);
	cub3d->south = mlx_load_png(cub3d->scene.south_texture);
	cub3d->east = mlx_load_png(cub3d->scene.east_texture);
	cub3d->west = mlx_load_png(cub3d->scene.west_texture);
	if (!cub3d->north || !cub3d->south || !cub3d->east || !cub3d->west)
	{
		free_map(cub3d->map);
		if (cub3d->north)
			mlx_delete_texture(cub3d->north);
		if (cub3d->west)
			mlx_delete_texture(cub3d->west);
		if (cub3d->east)
			mlx_delete_texture(cub3d->east);
		if (cub3d->south)
			mlx_delete_texture(cub3d->south);
		panic_exit("", &cub3d->scene);
	}
}

void	set_pos_and_dir(t_cub3d *cub3d)
{
	int		i;
	int		j;

	i = -1;
	while (cub3d->map[++i])
	{
		j = -1;
		while (cub3d->map[i][++j])
		{
			if (ft_strchr("NSEW", cub3d->map[i][j]))
			{
				update_vector(&cub3d->player.pos,
					(j * TILE_SIZE + TILE_SIZE / 2.0),
					(i * TILE_SIZE + TILE_SIZE / 2.0));
				update_vector(&cub3d->player.map_pos, j, i);
				init_direction(cub3d, cub3d->map[i][j]);
				return ;
			}
		}
	}
}

void	init_values(t_cub3d *cub3d)
{
	cub3d->mlx = NULL;
	cub3d->image = NULL;
	cub3d->map = push_map(&cub3d->scene.map);
	init_textures(cub3d);
	set_pos_and_dir(cub3d);
	update_vector(&cub3d->ray, 0, 0);
	update_vector(&cub3d->player.delta_dist, 0, 0);
	update_vector(&cub3d->player.step, 0, 0);
	update_vector(&cub3d->player.dist_to_side, 0, 0);
	cub3d->is_moving = 1;
	cub3d->player.angle = 0.0;
}

int	init_game(t_cub3d *cub3d)
{
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	cub3d->mlx = mlx_init(WIDTH, HEIGHT, "Cub3d", true);
	if (!cub3d->mlx)
		return (EXIT_FAILURE);
	cub3d->image = mlx_new_image(cub3d->mlx, WIDTH, HEIGHT);
	if (!cub3d->image)
	{
		mlx_terminate(cub3d->mlx);
		return (EXIT_FAILURE);
	}
	mlx_image_to_window(cub3d->mlx, cub3d->image, 0, 0);
	mlx_loop_hook(cub3d->mlx, &ft_hook, cub3d);
	mlx_key_hook(cub3d->mlx, &listen_moves, cub3d);
	mlx_loop(cub3d->mlx);
	return (EXIT_SUCCESS);
}

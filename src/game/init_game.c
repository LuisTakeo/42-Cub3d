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

#include "../../includes/cub3d.h"

void	move_to(t_vector *pos, t_vector dir, float speed)
{
	pos->x += dir.x * speed;
	pos->y += dir.y * speed;
}

void	listen_moves(mlx_key_data_t keydata, void *param)
{
	t_cub3d	*cub3d;

	cub3d = (t_cub3d *)param;
	if (keydata.key == MLX_KEY_W)
	{
		printf("Walking Front\n");

	}
	if (keydata.key == MLX_KEY_S)
	{
		printf("Walking Back\n");
		// cub3d->player.pos.y -= 0.1;
		// move_to(&cub3d->player.pos, cub3d->player.dir, -0.1);
	}
	if (keydata.key == MLX_KEY_A)
	{
		// printf("Walking Left\n");
		// cub3d->player.pos.x -= 0.1;
	}
	if (keydata.key == MLX_KEY_D)
	{
		// printf("Walking Right\n");
		// cub3d->player.pos.x += 0.1;
	}
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

void	init_direction(t_cub3d *cub3d, char direction)
{
	if (direction == 'N')
	{
		update_vector(&cub3d->player.dir, 0, -1);
		update_vector(&cub3d->player.cameraPlane, 0.66, 0);
	}
	if (direction == 'S')
	{
		update_vector(&cub3d->player.dir, 0, 1);
		update_vector(&cub3d->player.cameraPlane, -0.66, 0);
	}
	if (direction == 'W')
	{
		update_vector(&cub3d->player.dir, -1, 0);
		update_vector(&cub3d->player.cameraPlane, 0, -0.66);
	}
	if (direction == 'E')
	{
		update_vector(&cub3d->player.dir, 1, 0);
		update_vector(&cub3d->player.cameraPlane, 0, 0.66);
	}

}

void	init_values(t_cub3d *cub3d)
{
	cub3d->mlx = NULL;
	cub3d->map = ft_split(
		"1111111111\n"
		"1010000001\n"
		"1000000001\n"
		"1010001001\n"
		"1000000001\n"
		"1000000001\n"
		"1000000001\n"
		"1111111111"
		,'\n');
	update_vector(&cub3d->player.pos, (4.0 * TILE_SIZE + TILE_SIZE / 2.0),
		(5 * TILE_SIZE + TILE_SIZE / 2.0));
	init_direction(cub3d, 'W');
	// update_vector(&cub3d->plane, 0, 0);
	update_vector(&cub3d->ray, 0, 0);
	update_vector(&cub3d->player.delta_dist, 0, 0);
	update_vector(&cub3d->player.map_pos, 5, 5);
	update_vector(&cub3d->player.step, 0, 0);
	update_vector(&cub3d->player.dist_to_side, 0, 0);
	cub3d->player.angle = 0.0;
}


void	ft_hook(void* param)
{
	t_cub3d	*cub3d;

	cub3d = (t_cub3d *)param;
	draw_background(cub3d);
	draw_walls(cub3d);
}

int	init_game(t_cub3d *cub3d)
{
	// mlx_set_setting(MLX_MAXIMIZED, true);
	cub3d->mlx = mlx_init(WIDTH, HEIGHT, "Cub3d", false);
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
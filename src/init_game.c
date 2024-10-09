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

int	update_vector(t_vector *vector, float x, float y)
{
	if (!vector)
		return (EXIT_FAILURE);
	vector->x = x;
	vector->y = y;

	return (EXIT_SUCCESS);
}

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
		cub3d->player.pos.y += 0.1;
		move_to(&cub3d->player.pos, cub3d->player.dir, 0.1);
	}
	if (keydata.key == MLX_KEY_S)
	{
		printf("Walking Back\n");
		cub3d->player.pos.y -= 0.1;
		move_to(&cub3d->player.pos, cub3d->player.dir, -0.1);
	}
	if (keydata.key == MLX_KEY_A)
	{
		printf("Walking Left\n");
		cub3d->player.pos.x -= 0.1;
	}
	if (keydata.key == MLX_KEY_D)
	{
		printf("Walking Right\n");
		cub3d->player.pos.x += 0.1;
	}
	if (keydata.key == MLX_KEY_LEFT)
	{
		cub3d->player.angle += 0.03;
		printf("To the left\n"
			"Player angle: %f\n", cub3d->player.angle);
	}
	if (keydata.key == MLX_KEY_RIGHT)
	{
		cub3d->player.angle -= 0.03;
		printf("To the right\n"
			"Player angle: %f\n", cub3d->player.angle);
	}
	if (cub3d->player.angle > 2 * M_PI)
		cub3d->player.angle -= 2 * M_PI;
	if (cub3d->player.angle < 0)
		cub3d->player.angle += 2 * M_PI;
	cub3d->player.dir.x = cos(cub3d->player.angle);
	cub3d->player.dir.y = sin(cub3d->player.angle);
	printf("Player position: x = %f, y = %f\n", cub3d->player.pos.x, cub3d->player.pos.y);
	// printf("Player position: x = %f, y = %f\n", cub3d->player.pos.x / TILE_SIZE, cub3d->player.pos.y / TILE_SIZE);
	printf("Player direction: x = %f, y = %f\n", cub3d->player.dir.x, cub3d->player.dir.y);
}

void	init_values(t_cub3d *cub3d)
{
	cub3d->mlx = NULL;
	cub3d->map = NULL;
	update_vector(&cub3d->player.pos, (5.0 * TILE_SIZE + TILE_SIZE / 2.0),
		(2 * TILE_SIZE + TILE_SIZE / 2));
	update_vector(&cub3d->player.dir, -1.0, 0.0);
	update_vector(&cub3d->player.plane, 0.0, 0.66);
	update_vector(&cub3d->plane, 0, 0);
	update_vector(&cub3d->ray, 0, 0);
	cub3d->player.angle = 0.0;
}

void	draw_background(t_cub3d *cub3d)
{
	int	i;

	i = 0;
	while (i < WIDTH)
	{
		draw_vertical_line(cub3d->image, (t_vector){i, 0}, HEIGHT, 0xFFFFFFFF);
		i++;
	}
}


// void	draw_walls(t_cub3d	*cub3d)
// {
// 	int	i;

// 	i = 0;
// 	while (i < WIDTH)
// 	{
// 		i++;
// 	}
// }


static void ft_hook(void* param)
{
	t_cub3d	*cub3d;

	cub3d = (t_cub3d *)param;
	draw_background(cub3d);
	// draw_walls(cub3d);
}

int	init_game(t_cub3d *cub3d)
{
	// mlx_set_setting(MLX_MAXIMIZED, true);
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
	mlx_loop_hook(cub3d->mlx, &ft_hook, cub3d->mlx);
	mlx_key_hook(cub3d->mlx, &listen_moves, cub3d);
	mlx_loop(cub3d->mlx);
	return (EXIT_SUCCESS);
}
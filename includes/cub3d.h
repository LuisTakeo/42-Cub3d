/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaim-yu <tpaim-yu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 21:04:22 by tpaim-yu          #+#    #+#             */
/*   Updated: 2024/09/11 21:04:22 by tpaim-yu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# define TILE_SIZE 8.0
# define FOV 0.66
# define WIDTH 800
# define HEIGHT 600

# include <unistd.h>
# include <stdio.h>
# include <math.h>

# include "../lib/libft/libft.h"
# include "../lib/libft/gnl/includes/get_next_line.h"
# include "../lib/MLX42/include/MLX42/MLX42.h"

typedef struct s_vector	t_vector;
typedef struct s_player	t_player;
typedef struct s_cub3d	t_cub3d;

struct s_vector
{
	float	x;
	float	y;
};

struct s_player
{
	int			side;
	float		angle;
	t_vector	pos;
	t_vector	dir;
	t_vector	cameraPlane;
	t_vector	delta_dist;
	t_vector	dist_to_side;
	t_vector	map_pos;
	t_vector	step;
};

struct s_cub3d
{
	char		**map;
	mlx_t		*mlx;
	t_player	player;
	t_vector	ray;
	// t_vector	plane;
	mlx_image_t	*image;
};

void	init_values(t_cub3d *cub3d);
int		init_game(t_cub3d *cub3d);
void	finish_game(t_cub3d *cub3d);
// funções de draw
void	draw_background(t_cub3d *cub3d);
void	draw_vertical_line(mlx_image_t *image,
			t_vector vector, int y_end, int32_t color);
void	draw_ceiling(t_cub3d *cub3d);
void	draw_floor(t_cub3d *cub3d);
void	draw_walls(t_cub3d *cub3d);
// calculos de vetores
t_vector	sum_vector(t_vector v, t_vector z);
t_vector	multi_vector(t_vector v, double num);
t_vector	rotate_vector(t_vector v, float angle);
// raycasting
t_vector	find_ray_dir(t_cub3d *cub3d, int x);
t_vector	calculate_delta_dist(t_vector ray_dir);
int			update_vector(t_vector *vector, double x, double y);


#endif
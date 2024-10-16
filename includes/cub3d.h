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
# define TILE_SIZE 1.0
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
typedef struct s_wall	t_wall;

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
	t_vector	camera_plane;
	t_vector	delta_dist;
	t_vector	dist_to_side;
	t_vector	map_pos;
	t_vector	step;
};

struct s_wall
{
	int				wall_height;
	int				draw_start;
	int				draw_end;
	int				text_x;
	int				text_y;
	float			wall_point_x;
	float			tex_pos;
	float			tex_step;
	mlx_texture_t	*texture;
};

struct s_cub3d
{
	int				is_moving;
	char			**map;
	mlx_t			*mlx;
	t_player		player;
	t_vector		ray;
	mlx_image_t		*image;
	mlx_texture_t	*north;
	mlx_texture_t	*south;
	mlx_texture_t	*east;
	mlx_texture_t	*west;
};

void		init_values(t_cub3d *cub3d);
int			init_game(t_cub3d *cub3d);
void		finish_game(t_cub3d *cub3d);
// funções de draw
void		draw_background(t_cub3d *cub3d);
void		draw_vertical_line(mlx_image_t *image,
				t_vector vector, int y_end, int32_t color);
void		draw_ceiling(t_cub3d *cub3d);
void		draw_floor(t_cub3d *cub3d);
void		draw_walls(t_cub3d *cub3d);
// calculos de vetores
t_vector	sum_vector(t_vector v, t_vector z);
t_vector	multi_vector(t_vector v, double num);
t_vector	rotate_vector(t_vector v, float angle);
// raycasting - dda (digital differential analyzer)
t_vector	find_ray_dir(t_cub3d *cub3d, int x);
t_vector	calculate_delta_dist(t_vector ray_dir);
int			update_vector(t_vector *vector, double x, double y);
void		calculate_dist_to_side(t_cub3d *cub3d, t_vector ray_dir);
float		calculate_dda(t_cub3d *cub3d, t_vector ray_dir);
// hooks
void		listen_moves(mlx_key_data_t keydata, void *param);
void		ft_hook(void *param);
// movimentos
void		moving(t_cub3d *cub3d, t_vector dir, int is_positive, int is_x);
int			verify_signal(float value);
int			verify_margin(t_cub3d *cub3d, t_vector dir,
				t_vector new_pos, int is_x);
void		identify_move(t_cub3d *cub3d, mlx_key_data_t keydata);
// utils
int			ft_array_size(char **array);
int			get_rgba(int r, int g, int b, int a);
// free
void		free_map(char **map);

#endif
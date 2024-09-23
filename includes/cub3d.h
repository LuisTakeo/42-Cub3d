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

# include <string.h>
# include <unistd.h>
# include <stdio.h>
# include <math.h>

# include "../lib/libft/libft.h"
# include "../lib/libft/gnl/includes/get_next_line.h"
# include "../lib/MLX42/include/MLX42/MLX42.h"

# define S_W 1900 // screen width
# define S_H 1000 // screen height
# define TILE_SIZE 30 // tile size
# define FOV 60 // field of view
# define ROTATION_SPEED 0.035 // rotation speed
# define PLAYER_SPEED 4 // player speed

typedef struct s_cub3d	t_cub3d;
typedef struct s_player	t_player;
typedef struct s_ray	t_ray;
typedef struct s_data	t_data;

// player x position in pixels
// player y position in pixels
// player angle
// field of view in radians
// rotation flag
// left right flag
// up down flag
struct s_player
{
	int		plyr_x;
	int		plyr_y;
	double	angle;
	float	fov_rd;
	int		rot;
	int		l_r;
	int		u_d;
};

struct s_ray
{
	double	ray_ngl;
	double	distance;
	int		flag;
};

struct s_data
{
	char	**map2d;
	int		p_x;
	int		p_y;
	int		w_map;
	int		h_map;
};

struct s_cub3d
{
	mlx_t	*mlx;
	char	**map;
	mlx_image_t  *img; // the image
	mlx_t   *mlx_p; // the mlx pointer
	t_ray   *ray; // the ray structure
	t_data   *dt; // the data structure
	t_player  *ply; // the player structure
};

void	init_values(t_cub3d *cub3d);
int		init_game(t_cub3d *cub3d);
void	finish_game(t_cub3d *cub3d);

#endif
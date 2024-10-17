/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaim-yu <tpaim-yu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 21:04:22 by tpaim-yu          #+#    #+#             */
/*   Updated: 2024/10/17 17:36:02 by phraranha        ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# define TILE_SIZE 1.0
# define FOV 0.66
# define WIDTH 800
# define HEIGHT 600
# define VALID_M "01NEWS"
# define VALID_P "NEWS"

# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include <stdbool.h>
# include <stdlib.h>
# include <fcntl.h>

# include "../lib/libft/libft.h"
# include "../lib/libft/gnl/includes/get_next_line.h"
# include "../lib/MLX42/include/MLX42/MLX42.h"

typedef struct s_vector	t_vector;
typedef struct s_player	t_player;
typedef struct s_cub3d	t_cub3d;
typedef struct s_wall	t_wall;

typedef enum e_direction
{
	NORTH,
	SOUTH,
	WEST,
	EAST,
	INVALID_DIRECTION
}			t_direction;

typedef struct s_map
{
	char	**map;
	char	**map_data;
	int		map_width;
	int		map_height;
}			t_map;

typedef struct s_color
{
	int		r;
	int		g;
	int		b;
}			t_color;

typedef struct s_scene
{
	char	*north_texture;
	char	*south_texture;
	char	*west_texture;
	char	*east_texture;
	int		floor_color;
	int		ceiling_color;
	int		no_counter;
	int		so_counter;
	int		we_counter;
	int		ea_counter;
	int		f_counter;
	int		c_counter;
	int		invalid_c;
	char	**file_lines;
	int		line_count;
	t_map	map;
	bool	map_started;
	int		player_count;
}			t_scene;

typedef struct s_pos
{
	int		x;
	int		y;
}			t_pos;

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
	uint32_t		text_x;
	uint32_t		text_y;
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
	t_scene			scene;
};

// funções de inicialização e finalização
void			init_values(t_cub3d *cub3d);
int				init_game(t_cub3d *cub3d);
void			init_textures(t_cub3d *cub3d);
void			finish_game(t_cub3d *cub3d);
// funções de draw
void			draw_background(t_cub3d *cub3d);
void			draw_vertical_line(mlx_image_t *image,
					t_vector vector, int y_end, int32_t color);
void			draw_ceiling(t_cub3d *cub3d);
void			draw_floor(t_cub3d *cub3d);
void			draw_walls(t_cub3d *cub3d);
void			draw_line(t_cub3d *cub3d, t_wall wall, int x);
void			set_direction(t_cub3d *cub3d, t_vector ray);
mlx_texture_t	*select_texture(t_cub3d *cub3d);
// calculos de vetores
t_vector		sum_vector(t_vector v, t_vector z);
t_vector		multi_vector(t_vector v, double num);
t_vector		rotate_vector(t_vector v, float angle);
// raycasting - dda (digital differential analyzer)
t_vector		find_ray_dir(t_cub3d *cub3d, int x);
t_vector		calculate_delta_dist(t_vector ray_dir);
int				update_vector(t_vector *vector, double x, double y);
void			calculate_dist_to_side(t_cub3d *cub3d, t_vector ray_dir);
float			calculate_dda(t_cub3d *cub3d, t_vector ray_dir);
void			compare_and_calculate_x_and_y(t_cub3d *cub3d,
					t_vector *dda_line_size, t_vector *wall_map_pos);
float			calculate_return_of_dda(t_cub3d *cub3d, t_vector ray_dir,
					t_vector wall_map_pos);
// hooks
void			listen_moves(mlx_key_data_t keydata, void *param);
void			ft_hook(void *param);
// movimentos
void			moving(t_cub3d *cub3d, t_vector dir, int is_positive, int is_x);
int				verify_signal(float value);
int				verify_margin(t_cub3d *cub3d, t_vector dir,
					t_vector new_pos, int is_x);
void			identify_move(t_cub3d *cub3d, mlx_key_data_t keydata);
// utils
t_vector		filter_size(char **map, t_vector pos);
int				ft_array_size(char **array);
int				get_rgba(int r, int g, int b, int a);
uint32_t		get_pixel_color(mlx_texture_t *texture, int y, int x);
char			**push_map(t_map *map);
// free
void			free_map(char **map);
void			calculate_dist_to_side(t_cub3d *cub3d, t_vector ray_dir);
float			calculate_dda(t_cub3d *cub3d, t_vector ray_dir);
// hooks
void			listen_moves(mlx_key_data_t keydata, void *param);
void			ft_hook(void *param);
// movimentos
void			moving(t_cub3d *cub3d, t_vector dir, int is_positive, int is_x);
int				verify_signal(float value);
int				verify_margin(t_cub3d *cub3d, t_vector dir,
					t_vector new_pos, int is_x);
void			identify_move(t_cub3d *cub3d, mlx_key_data_t keydata);

// validações e afins
void			err(char *str);
void			err_exit(char *str);
void			free_line_array(char **lines, int count);
void			free_map_data(char **map_data, int height);
void			panic_exit(char *error_message, t_scene *scene);
void			panic(char *err_msg, t_scene *scene);
void			ok_free(char *err_msg, t_scene *scene);
void			*ft_realloc(void *ptr, size_t original_size, size_t new_size);
bool			is_whitespace(char c);
int				is_valid_color_value(int value);
void			print_map(char **map_data, int map_height, int map_width);
char			**read_file_lines(int fd, t_scene *scene);
void			free_components(char **components);
bool			validate_color_components(char **components);
int				parse_color(char *line);
bool			is_map_line(char *line);
void			count_texture_elements(char *line, t_scene *scene);
bool			handle_line(char *line, t_scene *scene, bool *map_started);
int				count_whitespace(char *c);
void			handle_texture(t_scene *scene, t_direction dir, char *line);
void			handle_floor_color(t_scene *scene, char *line);
void			handle_ceiling_color(t_scene *scene, char *line);
void			parse_scene_from_lines(char **lines, int line_count,
					t_scene *scene);
int32_t			rgb_to_hex(int r, int g, int b);
void			hex_to_rgb(int hex, int *r, int *g, int *b);
void			print_flood_filled_map(t_scene *scene, bool **filled_map);
int				check_map_surrounded(t_scene *scene, t_pos pos);
bool			is_valid_map_char(char c);
bool			is_player_char(char c);
bool			handle_map_line(char *line, bool *map_started);
void			calculate_map_width(char *line, int *map_width);
void			resize_map_data(t_scene *scene, int map_height);
void			copy_map_line(t_scene *scene, char *line, int map_height);
void			validate_map_characters(char *line, int current_width,
					t_scene *scene, t_pos *pos);
void			final_map_validation(t_scene *scene);
void			init_map_vars(t_scene scene);
void			parse_map_from_lines(char **lines, int line_count,
					t_scene *scene, t_pos *pos);
bool			count_elements_from_lines(char **lines, int line_count,
					t_scene *scene);
bool			is_directory(const char *filename);
bool			validate_extension(const char *filename, const char *ext);
bool			file_exists(const char *filename);
bool			is_empty(const char *filename);
bool			validate_file(const char *filename, const char *ext);
bool			validate_elements(t_scene *scene);
bool			valid_arg(int ac, char **av, int fd);
void			fill_map_with_twos(t_scene *scene);
char			**convert_to_split(t_scene *scene);
bool			is_valid_element_line(char *line);
void			parse_map_from_lines(char **lines, int line_count,
					t_scene *scene, t_pos *player_pos);
bool			non_map_line(char *line, bool *map_started);
bool			handle_map_line(char *line, bool *map_started);
bool			is_empty_line(char *line);

#endif

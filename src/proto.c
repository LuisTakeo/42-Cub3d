#include "../lib/libft/libft.h"
#include "get_next_line.h"
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define FT_VECTOR_INITIAL_CAPACITY 16

typedef struct s_vector
{
	char			**values;
	unsigned long	size;
	unsigned long	capacity;
}					t_vector;

typedef enum e_direction
{
	NORTH,
	SOUTH,
	WEST,
	EAST,
	INVALID_DIRECTION
}					t_direction;

typedef struct s_map
{
	char			**map;
	char			**map_data;
	int				map_width;
	int				map_height;
}					t_map;

typedef struct s_color
{
	int				r;
	int				g;
	int				b;
}					t_color;

typedef struct s_scene
{
	char			*north_texture;
	char			*south_texture;
	char			*west_texture;
	char			*east_texture;
	int				floor_color;
	int				ceiling_color;
	t_map			map;
	t_vector		vap;
}					t_scene;

typedef struct s_pos
{
	int				x;
	int				y;
}					t_pos;

void	*ft_realloc(void *ptr, size_t original_size, size_t new_size)
{
	void	*new;

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	else if (!ptr)
		return (malloc(new_size));
	else if (new_size <= original_size)
		return (ptr);
	else
	{
		new = malloc(new_size);
		if (!new)
		{
			free(ptr);
			return (NULL);
		}
		ft_memcpy(new, ptr, original_size);
		free(ptr);
		return (new);
	}
}

void	ft_vector_init(t_vector *vector)
{
	free(vector->values);
	vector->values = NULL;
	vector->capacity = 0;
	vector->size = 0;
}

bool	ft_vector_empty(const t_vector *vector)
{
	if (vector == NULL)
		return (true);
	return (vector->size == 0);
}

bool	ft_vector_resize(t_vector *vector, unsigned long new_capacity)
{
	char	*new_values;

	if (!vector)
		return (false);
	if ((int)new_capacity < 0)
		return (false);
	if (new_capacity == 0)
	{
		ft_vector_init(vector);
		return (true);
	}
	if (new_capacity < vector->size)
		new_capacity = vector->size;
	new_values = ft_realloc(vector->values, vector->capacity * sizeof(char *),
			new_capacity * sizeof(long));
	if (new_values == NULL)
		return (false);
	vector->values = &new_values;
	vector->capacity = new_capacity;
	if (new_capacity < vector->size)
		vector->size = new_capacity;
	return (true);
}

unsigned long	ft_vector_insert(t_vector *vector, unsigned long position,
		char *value)
{
	unsigned long	new_capacity;
	unsigned long	i;

	if (vector == NULL)
		return (0);
	if (position > vector->size)
		return (0);
	if (vector->size >= vector->capacity)
	{
		new_capacity = vector->capacity + (vector->capacity >> 1);
		if (!ft_vector_resize(vector, new_capacity))
			return (0);
	}
	i = vector->size;
	while (i > position)
	{
		vector->values[i] = vector->values[i - 1];
		--i;
	}
	vector->values[position] = value;
	vector->size++;
	return (position);
}

t_vector	*ft_vector_create(void)
{
	t_vector	*new_vector;

	new_vector = malloc(sizeof *new_vector);
	if (new_vector == NULL)
		return (NULL);
	new_vector->size = 0;
	new_vector->capacity = FT_VECTOR_INITIAL_CAPACITY;
	new_vector->values = malloc(new_vector->capacity * sizeof(char *));
	if (new_vector->values == NULL)
	{
		free(new_vector);
		return (NULL);
	}
	return (new_vector);
}

void	ft_vector_push_back(t_vector *vector, char *value)
{
	unsigned long	new_capacity;

	if (vector == NULL)
		return ;
	if (vector->size >= vector->capacity)
	{
		new_capacity = vector->capacity + (vector->capacity >> 1);
		if (!ft_vector_resize(vector, new_capacity))
			return ;
	}
	vector->values[vector->size] = value;
	vector->size++;
}

void	ft_vector_free(t_vector *vector)
{
	if (vector == NULL)
		return ;
	free(vector->values);
	free(vector);
}

t_direction	get_direction(char *identifier)
{
	if (ft_strncmp(identifier, "NO", 2) == 0)
		return (NORTH);
	if (ft_strncmp(identifier, "SO", 2) == 0)
		return (SOUTH);
	if (ft_strncmp(identifier, "WE", 2) == 0)
		return (WEST);
	if (ft_strncmp(identifier, "EA", 2) == 0)
		return (EAST);
	return (INVALID_DIRECTION);
}

void				load_map(int fd, char *first_line, t_scene *scene);
int	is_valid_color_value(int value)
{
	return (value >= 0 && value <= 255);
}

// t_color	parse_color(char *line)
//{
//	t_color	color;
//	char	**components;
//
//	components = ft_split(line, ',');
//	if (!components || !components[0] || !components[1] || !components[2])
//	{
//		printf("Error: Invalid color format\n");
//		exit(EXIT_FAILURE);
//	}
//	color.r = ft_atoi(components[0]);
//	color.g = ft_atoi(components[1]);
//	color.b = ft_atoi(components[2]);
//	if (!is_valid_color_value(color.r) || !is_valid_color_value(color.g)
//		|| !is_valid_color_value(color.b))
//	{
//		printf("Error: Color values must be between 0 and 255\n");
//		exit(EXIT_FAILURE);
//	}
//	free(components[0]);
//	free(components[1]);
//	free(components[2]);
//	free(components);
//	return (color);
//}

int	parse_color(char *line)
{
	char	**components;

	int r, g, b;
	components = ft_split(line, ',');
	if (!components)
	{
		perror("ft_split");
		exit(EXIT_FAILURE);
	}
	if (!components[0] || !components[1] || !components[2])
	{
		printf("Error: Invalid color format\n");
		exit(EXIT_FAILURE);
	}
	r = ft_atoi(components[0]);
	g = ft_atoi(components[1]);
	b = ft_atoi(components[2]);
	if (!is_valid_color_value(r) || !is_valid_color_value(g)
		|| !is_valid_color_value(b))
	{
		printf("Error: Color values must be between 0 and 255\n");
		exit(EXIT_FAILURE);
	}
	free(components[0]);
	free(components[1]);
	free(components[2]);
	free(components);
	return ((r << 16) | (g << 8) | b);
}
void	parse_scene(int fd, t_scene *scene)
{
	char		*line;
	t_direction	dir;
	int			color;
	int			r;
	int			g;
	int			b;

	while ((line = get_next_line(fd)) != NULL)
	{
		while (*line && (*line == ' ' || *line == '\n'))
			line++;
		dir = get_direction(line);
		if (dir != INVALID_DIRECTION)
		{
			if (dir == NORTH)
				scene->north_texture = ft_strdup(ft_strtrim(line + 3, "\n"));
			else if (dir == SOUTH)
				scene->south_texture = ft_strdup(ft_strtrim(line + 3, "\n"));
			else if (dir == WEST)
				scene->west_texture = ft_strdup(ft_strtrim(line + 3, "\n"));
			else if (dir == EAST)
				scene->east_texture = ft_strdup(ft_strtrim(line + 3, "\n"));
		}
		else if (*line == 'F')
			scene->floor_color = parse_color(line + 2);
		else if (*line == 'C')
			scene->ceiling_color = parse_color(line + 2);
		else if (ft_isdigit(*line) || *line == ' ' || *line == '\t')
		{
			load_map(fd, line, scene);
			break ;
		}
	}
	printf("Ceiling color: %#X\n", scene->ceiling_color);
	printf("Floor color: %#X\n", scene->floor_color);
	printf("North texture: %s\n",
		scene->north_texture ? scene->north_texture : "(null)");
	printf("South texture: %s\n",
		scene->south_texture ? scene->south_texture : "(null)");
	printf("West texture: %s\n",
		scene->west_texture ? scene->west_texture : "(null)");
	printf("East texture: %s\n",
		scene->east_texture ? scene->east_texture : "(null)");
	color = scene->floor_color;
	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = color & 0xFF;
	printf("Color - R: %d, G: %d, B: %d\n", r, g, b);
	free(line);
}

unsigned long	ft_vector_size(const t_vector *vector)
{
	if (vector == NULL)
		return (-1);
	return (vector->size);
}

unsigned long	ft_height(int fd)
{
	char	*line;
	int		i;

	i = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		if (ft_isdigit(*line) || *line == ' ' || *line == '\t')
			i++;
	}
	return (i);
}
// int	get_map_columns(const char *map)
//{
//	int	i;
//	int	max_cols;
//	int	current_cols;
//
//	i = 0;
//	max_cols = 0;
//	while (map[i] != '\0')
//	{
//		current_cols = ft_strlen(&map[i]);
//		if (current_cols > max_cols)
//			max_cols = current_cols;
//		i++;
//	}
//	return (max_cols);
//}
char	**vector_to_array(t_vector *vector)
{
	char			**array;
	unsigned long	i;

	array = malloc(sizeof(void *) * vector->size);
	if (!array)
		return (NULL);
	i = 0;
	while (i < vector->size)
	{
		array[i] = vector->values[i];
		printf("%s", array[i]);
		// printf("%s val \n", vector->values[i]);
		i++;
	}
	return (array);
}

int	get_map_columns2(t_vector *lines)
{
	int	i;
	int	max_cols;
	int	current_cols;

	i = 0;
	max_cols = 0;
	while (lines->values[i] != NULL)
	{
		//	int j = 0;
		current_cols = ft_strlen(lines->values[i]);
		//	while(lines->values[i][j])
		//	{
		//		if(lines->values[i][j] == '\t')
		//			current_cols += 3;
		//		j++;
		//	}
		printf("%d curre %d \n", current_cols, i);
		// printf("%s \n", (char *)lines->values[i]);
		if (current_cols > max_cols)
			max_cols = current_cols;
		i++;
	}
	return (max_cols);
}

void	load_map(int fd, char *first_line, t_scene *scene)
{
	t_vector	*map_lines;
	char		*line;
	int			i;

	map_lines = ft_vector_create();
	ft_vector_push_back(map_lines, first_line);
	while ((line = get_next_line(fd)) != NULL)
	{
		//	if (ft_isdigit(*line) || *line == ' ' || *line == '\t')
		ft_vector_push_back(map_lines, line);
	}
	scene->map.map_width = get_map_columns2(map_lines) - 1;
	scene->map.map_height = ft_vector_size(map_lines);
	//	scene->map.map_height = ft_height(fd);
	scene->map.map_data = vector_to_array(map_lines);
	//	scene->map.map_width = get_map_columns(*scene->map.map_data);
	printf("Map width: %d\n", scene->map.map_width);
	printf("Map height: %d\n", scene->map.map_height);
	i = 0;
	while (i < scene->map.map_height)
		printf("Map data: %s", scene->map.map_data[i++]);
	free(line);
	scene->vap = *map_lines;
	scene->map.map = scene->map.map_data;
	ft_vector_free(map_lines);
}

// int	flood_fill(char **map, int x, int y, int width, int height)
//{
//	if (x < 0 || y < 0 || x >= width || y >= height || map[y][x] == ' ')
//		return (0);
//	if (map[y][x] == '1' || map[y][x] == '2')
//		return (1);
//	map[y][x] = '2';
//	return (flood_fill(map, x + 1, y, width, height) && flood_fill(map, x - 1,
//			y, width, height) && flood_fill(map, x, y + 1, width, height)
//		&& flood_fill(map, x, y - 1, width, height));
//}

int	flood_fill(char **map, int x, int y, int width, int height)
{
	if (x < 0 || y < 0 || x >= width || y >= height || map[y][x] == ' ')
		return (0);
	if (map[y][x] == '1' || map[y][x] == '2')
		return (1);
	map[y][x] = '2';
	return (flood_fill(map, x + 1, y, width, height) && flood_fill(map, x - 1,
			y, width, height) && flood_fill(map, x, y + 1, width, height)
		&& flood_fill(map, x, y - 1, width, height));
}

bool	find_player_position(t_map *map, int *start_x, int *start_y)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->map_height)
	{
		j = 0;
		while (j < map->map_width)
		{
			if (map->map[i][j] == '0' || map->map[i][j] == 'N'
				|| map->map[i][j] == 'S' || map->map[i][j] == 'E'
				|| map->map[i][j] == 'W')
			{
				*start_x = j;
				*start_y = i;
				return (true);
			}
			j++;
		}
		i++;
	}
	return (false);
}

bool	validate_map(t_map *map)
{
	int	start_x;
	int	start_y;

	start_x = -1;
	start_y = -1;
	if (!find_player_position(map, &start_x, &start_y))
	{
		perror("No valid starting position found");
		return (false);
	}
	if (!flood_fill(map->map, start_x, start_y, map->map_width,
			map->map_height))
	{
		perror("Map is not enclosed by walls");
		return (false);
	}
	return (true);
}
bool	validate_extension(const char *filename, const char *ext)
{
	const char	*dot = ft_strrchr(filename, '.');

	return (dot && ft_strcmp(dot, ext) == 0);
}
bool	file_exists(const char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (false);
	close(fd);
	return (true);
}

bool	validate_file(const char *filename)
{
	//check if is empty
	if (!validate_extension(filename, ".cub"))
	{
		perror("Invalid file extension. Must be .cub");
		return (false);
	}
	return (true);
}

bool	validate_elements(t_scene *scene)
{
	if (!validate_extension(scene->north_texture, ".png")
		|| !validate_extension(scene->south_texture, ".png")
		|| !validate_extension(scene->west_texture, ".png")
		|| !validate_extension(scene->east_texture, ".png"))
	{
		perror("Invalid texture format");
		return (false);
	}
	if (!file_exists(scene->north_texture) || !file_exists(scene->south_texture)
		|| !file_exists(scene->west_texture)
		|| !file_exists(scene->east_texture))
	{
		perror("Texture file does not exist");
		return (false);
	}
	if (scene->ceiling_color == -1 || scene->floor_color == -1)
	{
		perror("Color values missing");
		return (false);
	}
	return (true);
}

int	main(int argc, char **argv)
{
	int		fd;
	t_scene	scene;

	if (argc != 2)
	{
		perror("Usage: ./cub3d <map_file.cub>");
		return (EXIT_FAILURE);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		return (EXIT_FAILURE);
	}
	if (!validate_file(argv[1]))
	{
		close(fd);
		return (EXIT_FAILURE);
	}
	parse_scene(fd, &scene);
	close(fd);
	if (!validate_elements(&scene))
	{
		perror("Invalid elements");
		return (EXIT_FAILURE);
	}
	if (!validate_map(&scene.map))
	{
		perror("Invalid map");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

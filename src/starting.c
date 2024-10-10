#include "../lib/libft/libft.h"
#include "get_next_line.h"
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define VALID_M "01NEWS"
#define VALID_P "NEWS"
#define WALL '1'
#define GROUND '0'
#define SPACE ' '
#define TAB '\t'

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

void	err(char *str)
{
	ft_putstr_fd("Error\n", STDERR_FILENO);
	ft_putendl_fd(str, STDERR_FILENO);
}

void	err_exit(char *str)
{
	ft_putstr_fd("Error\n", STDERR_FILENO);
	ft_putendl_fd(str, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	free_line_array(char **lines, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(lines[i]);
		i++;
	}
	free(lines);
}

void	free_map_data(char **map_data, int height)
{
	int	i;

	i = 0;
	if (map_data)
	{
		while (i < height)
		{
			if (map_data[i])
			{
				free(map_data[i]);
				map_data[i] = NULL;
			}
			i++;
		}
	}
}

void	panic_exit(char *error_message, t_scene *scene)
{
	err(error_message);
	free_map_data(scene->map.map_data, scene->map.map_height);
	free_line_array(scene->file_lines, scene->line_count);
	free(scene->map.map_data);
	free(scene->north_texture);
	free(scene->south_texture);
	free(scene->west_texture);
	free(scene->east_texture);
	exit(EXIT_FAILURE);
}

void	panic(char *err_msg, t_scene *scene)
{
	err(err_msg);
	if (scene->map.map_data)
		free_map_data(scene->map.map_data, scene->map.map_height);
	if (scene->file_lines)
		free_line_array(scene->file_lines, scene->line_count);
	free(scene->map.map_data);
	free(scene->north_texture);
	free(scene->south_texture);
	free(scene->west_texture);
	free(scene->east_texture);
	exit(EXIT_FAILURE);
}

void	ok_free(char *err_msg, t_scene *scene)
{
	err(err_msg);
	if (scene->map.map_data)
		free_map_data(scene->map.map_data, scene->map.map_height);
	if (scene->file_lines)
		free_line_array(scene->file_lines, scene->line_count);
	free(scene->map.map_data);
	free(scene->north_texture);
	free(scene->south_texture);
	free(scene->west_texture);
	free(scene->east_texture);
	exit(EXIT_SUCCESS);
}

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

bool	is_whitespace(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (true);
	else
		return (false);
}

int	is_valid_color_value(int value)
{
	return (value >= 0 && value <= 255);
}

void	print_map(char **map_data, int map_height, int map_width)
{
	int	i;

	i = 0;
	printf("Map (Height: %d, Width: %d):\n", map_height, map_width);
	while (i < map_height)
	{
		printf("%s", map_data[i]);
		i++;
	}
}

char	**read_file_lines(int fd, int *line_count)
{
	char	**lines;
	char	*line;
	int		count;

	count = 0;
	lines = NULL;
	line = get_next_line(fd);
	while (line != NULL)
	{
		lines = ft_realloc(lines, sizeof(char *) * count, sizeof(char *)
				* (count + 1));
		if (!lines)
			err_exit("Memory allocation failed");
		lines[count] = ft_strdup(line);
		if (!lines[count])
			err_exit("Memory allocation failed");
		count++;
		free(line);
		if (line != NULL)
			line = get_next_line(fd);
	}
	*line_count = count;
	return (lines);
}

void	free_components(char **components)
{
	int	i;

	i = 0;
	while (components[i])
	{
		free(components[i]);
		i++;
	}
	free(components);
}

bool	validate_color_components(char **components)
{
	if (!components[0] || !components[1] || !components[2])
	{
		err("Invalid color format");
		free_components(components);
		return (false);
	}
	if (ft_strlen(components[0]) > 3 || ft_strlen(components[1]) > 3
		|| ft_strlen(components[2]) > 3)
	{
		err("Error: Invalid color format (length)");
		free_components(components);
		return (false);
	}
	return (true);
}

int	parse_color(char *line)
{
	char	**components;
	int		r;
	int		g;
	int		b;

	components = ft_split(line, ',');
	if (!components)
		return (err("ft_split"), EXIT_FAILURE);
	if (!validate_color_components(components))
		return (EXIT_FAILURE);
	r = ft_atoi(components[0]);
	g = ft_atoi(components[1]);
	b = ft_atoi(components[2]);
	free_components(components);
	if (!is_valid_color_value(r) || !is_valid_color_value(g)
		|| !is_valid_color_value(b))
		return (err("Error: Color values must be between 0 and 255"),
			EXIT_FAILURE);
	return ((r << 16) | (g << 8) | b);
}

bool	is_map_line(char *line)
{
	return (ft_isdigit(*line) || *line == SPACE || *line == TAB);
}

void	count_texture_elements(char *line, t_scene *scene)
{
	t_direction	dir;

	dir = get_direction(line);
	if (dir == NORTH)
		scene->no_counter++;
	else if (dir == SOUTH)
		scene->so_counter++;
	else if (dir == WEST)
		scene->we_counter++;
	else if (dir == EAST)
		scene->ea_counter++;
	else if (*line == 'F')
		scene->f_counter++;
	else if (*line == 'C')
		scene->c_counter++;
}

bool	handle_line(char *line, t_scene *scene, bool *map_started)
{
	if (is_whitespace(*line))
		return (false);
	if (is_map_line(line))
	{
		*map_started = true;
		return (false);
	}
	count_texture_elements(line, scene);
	return (true);
}

int	count_whitespace(char *c)
{
	int	i;

	i = 0;
	while (*c == ' ' || (*c >= 9 && *c <= 13))
	{
		i++;
		c++;
	}
	return (i);
}

void	handle_texture(t_scene *scene, t_direction dir, char *line)
{
	char	*temp;

	temp = ft_strchr(line, ' ');
	if (temp)
	{
		temp++;
		while (is_whitespace(*temp))
			temp++;
		temp = ft_strtrim(temp, "\n ' ' '\t'");
		if (!temp)
		{
			free(line);
			return ;
		}
		if (dir == NORTH)
			scene->north_texture = ft_strdup(temp);
		else if (dir == SOUTH)
			scene->south_texture = ft_strdup(temp);
		else if (dir == WEST)
			scene->west_texture = ft_strdup(temp);
		else if (dir == EAST)
			scene->east_texture = ft_strdup(temp);
		free(temp);
	}
}

void	handle_floor_color(t_scene *scene, char *line)
{
	char	*temp;

	temp = ft_strchr(line, ' ');
	if (temp)
	{
		temp++;
		while (is_whitespace(*temp))
			temp++;
		temp = ft_strtrim(temp, "\n ' ' '\t'");
		if (!temp)
		{
			free(line);
			return ;
		}
		scene->floor_color = parse_color(temp);
	}
	free(temp);
}

void	handle_ceiling_color(t_scene *scene, char *line)
{
	char	*temp;

	temp = ft_strchr(line, ' ');
	if (temp)
	{
		temp++;
		while (is_whitespace(*temp))
			temp++;
		temp = ft_strtrim(temp, "\n ' ' '\t'");
		if (!temp)
		{
			free(line);
			return ;
		}
		scene->ceiling_color = parse_color(temp);
	}
	free(temp);
}

void	parse_scene_from_lines(char **lines, int line_count, t_scene *scene)
{
	int			i;
	char		*line;
	t_direction	dir;

	i = 0;
	while (i < line_count)
	{
		line = lines[i];
		dir = get_direction(line);
		if (dir != INVALID_DIRECTION)
			handle_texture(scene, dir, line);
		else if (*line == 'F')
			handle_floor_color(scene, line);
		else if (*line == 'C')
			handle_ceiling_color(scene, line);
		i++;
	}
}

int	rgb_to_hex(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

void	hex_to_rgb(int hex, int *r, int *g, int *b)
{
	*r = (hex >> 16) & 0xFF;
	*g = (hex >> 8) & 0xFF;
	*b = hex & 0xFF;
}

void	print_flood_filled_map(t_scene *scene, bool **filled_map)
{
	int	i;
	int	j;

	i = 0;
	while (i < scene->map.map_height)
	{
		j = 0;
		while (j < scene->map.map_width)
		{
			if (filled_map[i][j])
				ft_putchar_fd('#', 2);
			else
				ft_putchar_fd(scene->map.map_data[i][j], 2);
			j++;
		}
		ft_putchar_fd('\n', 2);
		i++;
	}
}

static bool	floodfill(t_scene *scene, bool **filled_map, int i, int j)
{
	bool	is_surrounded;

	if (i < 0 || i >= scene->map.map_height || j < 0
		|| j >= scene->map.map_width)
		return (false);
	if (scene->map.map_data[i][j] == '1' || filled_map[i][j] == true)
		return (true);
	else
		filled_map[i][j] = true;
	is_surrounded = true;
	is_surrounded &= floodfill(scene, filled_map, i - 1, j);
	is_surrounded &= floodfill(scene, filled_map, i + 1, j);
	is_surrounded &= floodfill(scene, filled_map, i, j - 1);
	is_surrounded &= floodfill(scene, filled_map, i, j + 1);
	return (is_surrounded);
}

int	check_map_surrounded(t_scene *scene, t_pos pos)
{
	int		x;
	int		y;
	int		i;
	bool	**filled_map;
	bool	is_surrounded;

	x = pos.x;
	y = pos.y;
	filled_map = ft_calloc(scene->map.map_height + 1, sizeof(bool *));
	i = 0;
	while (i < scene->map.map_height)
	{
		filled_map[i] = ft_calloc(scene->map.map_width, sizeof(bool));
		if (!filled_map[i])
		{
			free_line_array((char **)filled_map, scene->map.map_height);
			err_exit("malloc failed");
		}
		i++;
	}
	is_surrounded = floodfill(scene, filled_map, y, x);
	free_line_array((char **)filled_map, scene->map.map_height);
	if (!is_surrounded)
		panic("not surrounded", scene);
	return (0);
}

bool	is_valid_map_char(char c)
{
	return (c == '1' || c == '0' || c == ' ' || c == '\t' || c == '\n');
}

bool	is_player_char(char c)
{
	return (c == 'N' || c == 'W' || c == 'E' || c == 'S');
}

bool	handle_map_line(char *line, bool *map_started)
{
	if (is_map_line(&line[0]))
	{
		*map_started = true;
	}
	else if (!is_map_line(line) && *map_started)
	{
		err("Stopped parsing at non-map line after map started.");
		return (false);
	}
	return (true);
}

void	calculate_map_width(char *line, int *map_width)
{
	int	current_width;

	current_width = ft_strlen(line);
	while (current_width > 0 && is_whitespace(line[current_width - 1]))
		current_width--;
	if (current_width > *map_width)
		*map_width = current_width;
}

void	resize_map_data(t_scene *scene, int map_height)
{
	scene->map.map_data = ft_realloc(scene->map.map_data, sizeof(char *)
			* map_height, sizeof(char *) * (map_height + 1));
	if (!scene->map.map_data)
	{
		err("Memory allocation failed");
		exit(EXIT_FAILURE);
	}
}

void	copy_map_line(t_scene *scene, char *line, int map_height)
{
	scene->map.map_data[map_height] = ft_strdup(line);
	if (!scene->map.map_data[map_height])
	{
		err("Memory allocation failed");
		exit(EXIT_FAILURE);
	}
}

void	validate_map_characters(char *line, int current_width, t_scene *scene,
		t_pos *player_pos)
{
	int		j;
	char	c;

	j = 0;
	while (j < current_width)
	{
		c = line[j];
		if (is_player_char(c))
		{
			scene->player_count++;
			player_pos->x = j + 1;
			player_pos->y = scene->map.map_height + 1;
		}
		else if (!is_valid_map_char(c))
			scene->invalid_c++;
		j++;
	}
}

void	final_map_validation(t_scene *scene)
{
	if (scene->player_count != 1)
		panic("This is not a multiplayer game", scene);
	if (scene->invalid_c > 0)
		panic("Invalid characters in map", scene);
}

void	init_map_vars(t_scene scene)
{
	scene.map.map_height = 0;
	scene.map.map_width = 0;
	scene.player_count = 0;
	scene.map_started = false;
	scene.invalid_c = 0;
}

void	parse_map_from_lines(char **lines, int line_count, t_scene *scene,
		t_pos *player_pos)
{
	char	*line;
	int		i;

	init_map_vars(*scene);
	i = 0;
	scene->map.map_data = NULL;
	while (i < line_count)
	{
		line = lines[i];
		if (!handle_map_line(line, &scene->map_started))
			break ;
		if (scene->map_started)
		{
			calculate_map_width(line, &scene->map.map_width);
			resize_map_data(scene, scene->map.map_height);
			copy_map_line(scene, line, scene->map.map_height);
			validate_map_characters(line, ft_strlen(line), scene, player_pos);
			scene->map.map_height++;
		}
		i++;
	}
	final_map_validation(scene);
}

bool	count_elements_from_lines(char **lines, int line_count, t_scene *scene)
{
	bool	map_started;
	int		i;
	char	*line;

	map_started = false;
	i = 0;
	while (i < line_count && !map_started)
	{
		line = lines[i];
		if (is_whitespace(*line))
		{
			i++;
			continue ;
		}
		if (is_map_line(line))
			map_started = true;
		else
			count_texture_elements(line, scene);
		i++;
	}
	if (scene->no_counter != 1 || scene->so_counter != 1
		|| scene->we_counter != 1 || scene->ea_counter != 1
		|| scene->f_counter != 1 || scene->c_counter != 1)
		return (err("Missing or repeated elements"), false);
	return (true);
}

bool	is_directory(const char *filename)
{
	int	fd;

	fd = open(filename, __O_DIRECTORY);
	if (fd == -1)
		return (false);
	close(fd);
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

bool	is_empty(const char *filename)
{
	char	buffer[1];
	int		fd;

	fd = open(filename, O_RDONLY);
	if (read(fd, buffer, sizeof(buffer)) == 0)
	{
		return (false);
	}
	close(fd);
	return (true);
}

bool	validate_file(const char *filename)
{
	if (is_directory(filename))
	{
		err("Invalid file. Must be a file");
		return (false);
	}
	if (!validate_extension(filename, ".cub"))
	{
		err("Invalid file extension. Must be .cub");
		return (false);
	}
	if (!is_empty(filename))
	{
		err("emptyyyyy");
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
		err("Invalid texture format");
		return (false);
	}
	if (!file_exists(scene->north_texture) || !file_exists(scene->south_texture)
		|| !file_exists(scene->west_texture)
		|| !file_exists(scene->east_texture))
	{
		err("Texture file does not exist");
		return (false);
	}
	if (scene->ceiling_color == -1 || scene->floor_color == -1)
	{
		err("Color values missing");
		return (false);
	}
	return (true);
}

bool	valid_arg(int ac, char **av, int fd)
{
	if (ac != 2)
		return (err("Usage: ./cub3d <map_file.cub>"), false);
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return (err("Error opening file"), false);
	if (!validate_file(av[1]))
		return (false);
	return (true);
}

int	main(int argc, char **argv)
{
	int		fd;
	t_scene	scene;
	char	**file_lines;
	int		line_count;
	t_pos	pos;

	fd = 0;
	ft_memset(&scene, 0, sizeof(t_scene));
	if (!valid_arg(argc, argv, fd))
		return (EXIT_FAILURE);
	fd = open(argv[1], O_RDONLY);
	file_lines = read_file_lines(fd, &line_count);
	scene.file_lines = file_lines;
	scene.line_count = line_count;
	close(fd);
	if (!count_elements_from_lines(file_lines, line_count, &scene))
		return (free_line_array(file_lines, line_count), EXIT_FAILURE);
	parse_scene_from_lines(file_lines, line_count, &scene);
	if (!validate_elements(&scene))
		panic("invalid elements", &scene);
	parse_map_from_lines(file_lines, line_count, &scene, &pos);
	check_map_surrounded(&scene, pos);
	ok_free("ok", &scene);
}

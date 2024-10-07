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
	t_map	map;
}			t_scene;

typedef struct s_pos
{
	int		x;
	int		y;
}			t_pos;

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

void	print_map(char **map_data, int map_height, int map_width)
{
	int	i;

	i = 0;
	printf("Map (Height: %d, Width: %d):\n", map_height, map_width);
	while (i < map_height)
	{
		printf("%s\n", map_data[i]);
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
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("Read line: %s", line); // Debugging line
		lines = ft_realloc(lines, sizeof(char *) * count, sizeof(char *)
				* (count + 1));
		if (!lines)
		{
			perror("Memory allocation failed");
			exit(EXIT_FAILURE);
		}
		lines[count] = ft_strdup(line);
		if (!lines[count])
		{
			perror("Memory allocation failed");
			exit(EXIT_FAILURE);
		}
		count++;
		free(line);
	}
	*line_count = count;
	return (lines);
}
int	parse_color(char *line)
{
	char	**components;

	int r, g, b;
	components = ft_split(line, ',');
	if (!components)
	{
		perror("ft_split");
		return (EXIT_FAILURE);
	}
	if (!components[0] || !components[1] || !components[2])
	{
		printf("Error: Invalid color format\n");
		free(components[0]);
		free(components[1]);
		free(components[2]);
		free(components);
		return (EXIT_FAILURE);
	}
	if (ft_strlen(components[0]) > 3 || ft_strlen(components[1]) > 3
		|| ft_strlen(components[2]) > 3)
	{
		printf("Error: Invalid color format(len)\n");
		free(components[0]);
		free(components[1]);
		free(components[2]);
		free(components);
		return (EXIT_FAILURE);
	}
	r = ft_atoi(components[0]);
	g = ft_atoi(components[1]);
	b = ft_atoi(components[2]);
	if (!is_valid_color_value(r) || !is_valid_color_value(g)
		|| !is_valid_color_value(b))
	{
		printf("Error: Color values must be between 0 and 255\n");
		return (EXIT_FAILURE);
	}
	free(components[0]);
	free(components[1]);
	free(components[2]);
	free(components);
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
		scene->floor_color = parse_color(temp);
	}
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
		scene->ceiling_color = parse_color(temp);
	}
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

void	flood_fill(char **map, int width, int height, int x, int y)
{
	if (x < 0 || y < 0 || x >= width || y >= height)
		return ;
	if (map[y][x] == '1' || map[y][x] == 'F') 
		return ;
	map[y][x] = 'F';
	flood_fill(map, width, height, x + 1, y); 
	flood_fill(map, width, height, x - 1, y); 
	flood_fill(map, width, height, x, y + 1); 
	flood_fill(map, width, height, x, y - 1); 
}

bool	validate_map_enclosure(char **map, int width, int height,
		t_pos player_pos)
{
	char	**map_copy;
	int		i;
	int		y;
	int		x;

	map_copy = malloc(sizeof(char *) * height);
	i = 0;
	while (i < height)
	{
		map_copy[i] = ft_strdup(map[i]);
		i++;
	}
	flood_fill(map_copy, width, height, player_pos.x, player_pos.y);
	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			if (map_copy[y][x] == '0')
			{
				printf("Error: Open space not enclosed by walls at position (%d, %d).\n", x, y);
				free_line_array(map_copy, height);
				return (false);
			}
			x++;
		}
		y++;
	}
	free_line_array(map_copy, height);
	return (true);
}

bool	is_valid_map_char(char c)
{
	return (c == '1' || c == '0' || c == ' ' || c == '\t');
}

bool	is_player_char(char c)
{
	return (c == 'N' || c == 'W' || c == 'E' || c == 'S');
}

void	parse_map_from_lines(char **lines, int line_count, t_scene *scene,
		t_pos *player_pos)
{
	int		map_height;
	int		map_width;
	int		player_count;
	bool	map_started;
	char	*line;
	int		i;
	int		j;
	int		current_width;
	char	c;

	map_height = 0;
	map_width = 0;
	player_count = 0;
	map_started = false;
	i = 0;
	scene->map.map_data = NULL;
	while (i < line_count)
	{
		line = lines[i];
		if (is_map_line(&line[0]))
		{
			map_started = true;
		}
		if (!is_map_line(line) && map_started)
		{
			printf("Stopped parsing at non-map line after map started.\n");
			break ;
		}
		current_width = ft_strlen(line);
		while (current_width > 0 && is_whitespace(line[current_width - 1]))
			current_width--;
		if (current_width > map_width)
			map_width = current_width;
		scene->map.map_data = ft_realloc(scene->map.map_data, sizeof(char *)
				* map_height, sizeof(char *) * (map_height + 1));
		if (!scene->map.map_data)
		{
			perror("Memory allocation failed");
			exit(EXIT_FAILURE);
		}
		scene->map.map_data[map_height] = ft_strdup(line);
		if (!scene->map.map_data[map_height])
		{
			perror("Memory allocation failed");
			exit(EXIT_FAILURE);
		}
		if (map_started)
		{
			j = 0;
			while (j < current_width)
			{
				c = line[j];
				if (is_player_char(c))
				{
					player_count++;
					if (player_count > 1)
					{
						printf("Error: More than one player character found.\n");
						exit(EXIT_FAILURE);
					}
					player_pos->x = j;
					player_pos->y = map_height + 1;
				}
				else if (!is_valid_map_char(c) && map_started)
				{
					printf("Error: Invalid character '%c' found in map.\n", c);
					exit(EXIT_FAILURE);
				}
				j++;
			}
		}
		if(map_started)
			map_height++;
		i++;
	}
	if (player_count == 0)
	{
		printf("Error: No player character found in the map.\n");
		exit(EXIT_FAILURE);
	}
	scene->map.map_height = map_height;
	scene->map.map_width = map_width;
	printf("Map width: %d, Map height: %d\n", scene->map.map_width,
		scene->map.map_height);
	printf("Player found at position: (%d, %d)\n", player_pos->x,
		player_pos->y);
}

bool	count_elements_from_lines(char **lines, int line_count, t_scene *scene)
{
	bool	map_started;
	int		i;
	char	*line;

	map_started = false;
	i = 0;
	while (i < line_count)
	{
		line = lines[i];
		printf("Processing line %d: %s", i, line);
		if (is_whitespace(*line))
		{
			printf("Line %d is whitespace.\n", i);
			i++;
			continue ;
		}
		if (is_map_line(line))
		{
			printf("Map line detected at line %d: %s\n", i, line);
			map_started = true;
		}
		else
		{
			count_texture_elements(line, scene);
			printf("Texture/Element Counters - NO: %d, SO: %d, WE: %d, EA: %d,F:%d, C: %d\n", scene->no_counter, scene->so_counter,
				scene->we_counter, scene->ea_counter, scene->f_counter,
					scene->c_counter); 
		}
		i++;
	}
	if (scene->no_counter != 1 || scene->so_counter != 1
		|| scene->we_counter != 1 || scene->ea_counter != 1
		|| scene->f_counter != 1 || scene->c_counter != 1)
	{
		perror("Missing or repeated elements");
		return (false);
	}
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
		perror("Invalid file. Must be a file");
		return (false);
	}
	if (!validate_extension(filename, ".cub"))
	{
		perror("Invalid file extension. Must be .cub");
		return (false);
	}
	if (!is_empty(filename))
	{
		perror("emptyyyyy");
		return (false);
	}
	return (true);
}
bool	validate_elements(t_scene *scene)
{
	// if (scene->no_counter != 1 || scene->so_counter != 1
	//	|| scene->we_counter != 1 || scene->ea_counter != 1
	//	|| scene->f_counter != 1 || scene->c_counter != 1)
	//{
	//	perror("missing or repeated elements");
	//	return (false);
	//}
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
	// if is_empty?
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
	char	**file_lines;
	int		line_count;
	t_pos	pos;

	ft_memset(&scene, 0, sizeof(t_scene));
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
	file_lines = read_file_lines(fd, &line_count);
	close(fd);
	if (!count_elements_from_lines(file_lines, line_count, &scene))
	{
		free_line_array(file_lines, line_count);
		return (EXIT_FAILURE);
	}
	parse_scene_from_lines(file_lines, line_count, &scene);
	parse_map_from_lines(file_lines, line_count, &scene, &pos);
	free_line_array(file_lines, line_count);
	free(scene.map.map_data);
	free(scene.north_texture);
	free(scene.south_texture);
	free(scene.west_texture);
	free(scene.east_texture);
	return (EXIT_SUCCESS);
}

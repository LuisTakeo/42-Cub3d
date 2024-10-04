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

bool	count_elements(int fd, t_scene *scene)
{
	char	*line;
	bool	map_started;
	bool	success;

	map_started = false;
	success = true;
	while (true)
	{
		line = get_next_line(fd); 
		if (line == NULL)
			break ;
		if (!handle_line(line, scene, &map_started))
		{
			free(line);
			continue ; 
		}
		free(line);
	}
	if (scene->no_counter != 1 || scene->so_counter != 1
		|| scene->we_counter != 1 || scene->ea_counter != 1
		|| scene->f_counter != 1 || scene->c_counter != 1)
	{
		perror("missing/repeated elements");
		success = false;
	}
	return (success); 
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
		temp = ft_strtrim(temp, "\n");
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

void	parse_scene(int fd, t_scene *scene)
{
	char		*line;
	t_direction	dir;

	line = get_next_line(fd);
	while (line != NULL)
	{
		while (*line && is_whitespace(*line))
		{
			free(line);
			line = get_next_line(fd);
			if (line == NULL)
				break ;
		}
		if (line == NULL)
			break ;
		dir = get_direction(line);
		if (dir != INVALID_DIRECTION)
			handle_texture(scene, dir, line);
		else if (*line == 'F')
			handle_floor_color(scene, line);
		else if (*line == 'C')
			handle_ceiling_color(scene, line);
		free(line);
		line = get_next_line(fd);
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

void	parse_map(int fd, t_scene *scene)
{
	char	*line;
	int		map_height;
	int		map_width;
	int		current_width;

	map_height = 0;
	map_width = 0;
	scene->map.map_data = NULL;

	while ((line = get_next_line(fd)) != NULL)
	{
		if (!is_map_line(line))
		{
			free(line);
			continue;
		}

		current_width = ft_strlen(line);
		while (current_width > 0 && is_whitespace(line[current_width - 1]))
			current_width--;

		if (current_width > map_width)
			map_width = current_width;

		scene->map.map_data = ft_realloc(scene->map.map_data, sizeof(char *) * (map_height), sizeof(char *) * (map_height + 1));
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
		map_height++;
		free(line);
	}
	scene->map.map_height = map_height;
	scene->map.map_width = map_width;

	printf("%d width \n", scene->map.map_width);
	printf("%d height \n", scene->map.map_height);
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

	//	t_map	map;
	// init
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
	if (!validate_file(argv[1]))
	{
		close(fd);
		return (EXIT_FAILURE);
	}
	if (!count_elements(fd, &scene))
	{
		close(fd);
		return (EXIT_FAILURE);
	}
	fd = open(argv[1], O_RDONLY);
	parse_scene(fd, &scene /*, &map*/);
	close(fd);
	fd = open(argv[1], O_RDONLY);
	parse_map(fd, &scene);
	close(fd);
	free(scene.map.map_data);
	printf("alou");
	if (!validate_elements(&scene))
	{
		free(scene.north_texture);
		free(scene.south_texture);
		free(scene.west_texture);
		free(scene.east_texture);
		perror("Invalid elements");
		return (EXIT_FAILURE);
	}
	free(scene.north_texture);
	free(scene.south_texture);
	free(scene.west_texture);
	free(scene.east_texture);
	//	if (!validate_map(&scene.map))
	//	{
	//		perror("Invalid map");
	//		return (EXIT_FAILURE);
	//	}
	return (EXIT_SUCCESS);
}


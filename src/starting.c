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
	t_vector		vap;
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
	int				no_counter;
	int				so_counter;
	int				we_counter;
	int				ea_counter;
	int				f_counter;
	int				c_counter;
	t_map			map;
	t_vector		vap;
}					t_scene;

typedef struct s_pos
{
	int				x;
	int				y;
}					t_pos;

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
		exit(EXIT_FAILURE);
	}
	if (!components[0] || !components[1] || !components[2])
	{
		printf("Error: Invalid color format\n");
		exit(EXIT_FAILURE);
	}
	if (ft_strlen(components[0]) > 3 || ft_strlen(components[1]) > 3
		|| ft_strlen(components[2]) > 3)
	{
		printf("Error: Invalid color format(len)\n");
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

// void	parse_scene(int fd, t_scene *scene/*, t_map *map*/)
//{
//	char		*line;
//	t_direction	dir;
//	int			color;
//	int			r;
//	int			g;
//	int			b;
//
//	line = get_next_line(fd);
//	while (line != NULL)
//	{
//		while (*line && (*line == ' ' || *line == '\n'))
//			line++;
//		dir = get_direction(line);
//		if (dir != INVALID_DIRECTION)
//		{
//			if (dir == NORTH)
//			{
//				scene->north_texture = ft_strdup(ft_strtrim(line + 3, "\n"));
//				scene->no_counter++;
//			}
//			else if (dir == SOUTH)
//			{
//				scene->south_texture = ft_strdup(ft_strtrim(line + 3, "\n"));
//				scene->so_counter++;
//			}
//			else if (dir == WEST)
//			{
//				scene->west_texture = ft_strdup(ft_strtrim(line + 3, "\n"));
//				scene->we_counter++;
//			}
//			else if (dir == EAST)
//			{
//				scene->east_texture = ft_strdup(ft_strtrim(line + 3, "\n"));
//				scene->ea_counter++;
//			}
//		}
//		else if (*line == 'F')
//		{
//			scene->floor_color = parse_color(line + 2);
//			scene->f_counter++;
//		}
//		else if (*line == 'C')
//		{
//			scene->ceiling_color = parse_color(line + 2);
//			scene->c_counter++;
//		}
//		//	else if (ft_isdigit(*line) || *line == ' ' || *line == '\t')
//		//	{
//		//		load_map(fd, line, scene, map);
//		//		free(line);
//		//		break ;
//		//	}
//		free(line);
//		line = get_next_line(fd);
//	}
//	printf("Ceiling color: %#X\n", scene->ceiling_color);
//	printf("Floor color: %#X\n", scene->floor_color);
//	printf("North texture: %s\n",
//		scene->north_texture ? scene->north_texture : "(null)");
//	printf("South texture: %s\n",
//		scene->south_texture ? scene->south_texture : "(null)");
//	printf("West texture: %s\n",
//		scene->west_texture ? scene->west_texture : "(null)");
//	printf("East texture: %s\n",
//		scene->east_texture ? scene->east_texture : "(null)");
//	color = scene->floor_color;
//	r = (color >> 16) & 0xFF;
//	g = (color >> 8) & 0xFF;
//	b = color & 0xFF;
//	printf("Color - R: %d, G: %d, B: %d\n", r, g, b);
//	free(line);
//}

void	parse_scene(int fd, t_scene *scene /*, t_map *map*/)
{
	char		*line;
	char		*temp;
	t_direction	dir;
	int			color;
	int			r;
	int			g;
	int			b;

	line = get_next_line(fd);
	while (line != NULL)
	{
		while (*line && (*line == ' ' || *line == '\n'))
			line++;
		dir = get_direction(line);
		if (dir != INVALID_DIRECTION)
		{
			temp = ft_strtrim(line + 3, "\n");
			if (!temp)
			{
				free(line);
				return ; // Handle error or exit early
			}
			if (dir == NORTH)
			{
				scene->north_texture = ft_strdup(temp);
				scene->no_counter++;
			}
			else if (dir == SOUTH)
			{
				scene->south_texture = ft_strdup(temp);
				scene->so_counter++;
			}
			else if (dir == WEST)
			{
				scene->west_texture = ft_strdup(temp);
				scene->we_counter++;
			}
			else if (dir == EAST)
			{
				scene->east_texture = ft_strdup(temp);
				scene->ea_counter++;
			}
			free(temp); // Free temp after use
		}
		else if (*line == 'F')
		{
			scene->floor_color = parse_color(line + 2);
			scene->f_counter++;
		}
		else if (*line == 'C')
		{
			scene->ceiling_color = parse_color(line + 2);
			scene->c_counter++;
		}
		//	else if (ft_isdigit(*line) || *line == ' ' || *line == '\t')
		//	{
		//		load_map(fd, line, scene, map);
		//		free(line);
		//		break ;
		//	}
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
	color = scene->floor_color;
	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = color & 0xFF;
	printf("Color - R: %d, G: %d, B: %d\n", r, g, b);
	free(line);
}

bool	is_whitespace(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (true);
	else
		return (false);
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
	if (scene->no_counter != 1 || scene->so_counter != 1
		|| scene->we_counter != 1 || scene->ea_counter != 1
		|| scene->f_counter != 1 || scene->c_counter != 1)
	{
		perror("missing or repeated elements");
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
	parse_scene(fd, &scene /*, &map*/);
	close(fd);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phraranha <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 23:24:20 by phraranha         #+#    #+#             */
/*   Updated: 2024/10/14 14:09:20 by phraranha        ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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

bool	validate_file(const char *filename, const char *ext)
{
	if (is_directory(filename))
	{
		err("Invalid file. Must be a file");
		return (false);
	}
	if (!validate_extension(filename, ext))
	{
		err("Invalid file extension.");
		return (false);
	}
	if(ft_memcmp(ext, ".cub", 4) == 0)
	{
		if (!is_empty(filename))
		{
			err("emptyyyyy");
			return (false);
		}
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
	if(!validate_file(scene->north_texture, ".png") || !validate_file(scene->west_texture, ".png") || !validate_file(scene->east_texture, ".png") || !validate_file(scene->south_texture, ".png"))
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
	if (!validate_file(av[1], ".cub"))
		return (false);
	return (true);
}

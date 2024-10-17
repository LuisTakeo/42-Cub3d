/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaim-yu <tpaim-yu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 21:36:24 by tpaim-yu          #+#    #+#             */
/*   Updated: 2024/10/17 18:11:19 by phraranha        ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	okok(char *str)
{
	ft_putstr_fd("OK\n", STDERR_FILENO);
	ft_putendl_fd(str, STDERR_FILENO);
}

void	ok_free(char *ok_msg, t_scene *scene)
{
	printf("%s\n", ok_msg);
	if (scene->map.map_data)
		free_map_data(scene->map.map_data, scene->map.map_height);
	if (scene->file_lines)
		free_line_array(scene->file_lines, scene->line_count);
	free(scene->map.map_data);
	free(scene->north_texture);
	free(scene->south_texture);
	free(scene->west_texture);
	free(scene->east_texture);
}

bool	process_scene_and_map(t_scene *scene, t_pos *pos)
{
	if (!count_elements_from_lines(scene->file_lines, scene->line_count, scene))
	{
		free_line_array(scene->file_lines, scene->line_count);
		return (false);
	}
	parse_scene_from_lines(scene->file_lines, scene->line_count, scene);
	if (!validate_elements(scene))
		panic("Invalid elements", scene);
	parse_map_from_lines(scene->file_lines, scene->line_count, scene, pos);
	fill_map_with_twos(scene);
	check_map_surrounded(scene, *pos);
	return (true);
}

void	init_all(t_cub3d *cub3d, t_scene *scene, t_pos *pos, int *fd)
{
	ft_memset(cub3d, 0, sizeof(t_cub3d));
	ft_memset(scene, 0, sizeof(t_scene));
	ft_memset(pos, 0, sizeof(t_pos));
	*fd = 0;
}

int	main(int argc, char **argv)
{
	t_cub3d	cub3d;
	t_pos	pos;
	int		fd;

	init_all(&cub3d, &cub3d.scene, &pos, &fd);
	if (!valid_arg(argc, argv, fd))
		return (EXIT_FAILURE);
	fd = open(argv[1], O_RDONLY);
	cub3d.scene.file_lines = read_file_lines(fd, &cub3d.scene);
	close(fd);
	if (!process_scene_and_map(&cub3d.scene, &pos))
		return (EXIT_FAILURE);
	(void)cub3d;
	cub3d.map = cub3d.scene.map.map_data;
	init_values(&cub3d);
	init_game(&cub3d);
	finish_game(&cub3d);
	return (EXIT_SUCCESS);
}

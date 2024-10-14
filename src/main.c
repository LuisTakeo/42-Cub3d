/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaim-yu <tpaim-yu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 21:36:24 by tpaim-yu          #+#    #+#             */
/*   Updated: 2024/10/14 19:44:57 by paranha          ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
void	okok(char *str)
{
	ft_putstr_fd("OK\n", STDERR_FILENO);
	ft_putendl_fd(str, STDERR_FILENO);
}
void	ok_free(char *err_msg, t_scene *scene)
{
	okok(err_msg);
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
//int	main(int argc, char **argv)
//{
//	int		fd;
//	t_scene	scene;
//	char	**file_lines;
//	int		line_count;
//	t_pos	pos;
//
//	fd = 0;
//	ft_memset(&scene, 0, sizeof(t_scene));
//	if (!valid_arg(argc, argv, fd))
//		return (EXIT_FAILURE);
//	fd = open(argv[1], O_RDONLY);
//	file_lines = read_file_lines(fd, &line_count);
//	scene.file_lines = file_lines;
//	scene.line_count = line_count;
//	close(fd);
//	if (!count_elements_from_lines(file_lines, line_count, &scene))
//		return (free_line_array(file_lines, line_count), EXIT_FAILURE);
//	parse_scene_from_lines(file_lines, line_count, &scene);
//	if (!validate_elements(&scene))
//		panic("invalid elements", &scene);
//	parse_map_from_lines(file_lines, line_count, &scene, &pos);
//	fill_map_with_zeros(&scene);
//	check_map_surrounded(&scene, pos);
//	printf("%s \n", scene.north_texture);
//	printf("%s \n", scene.south_texture);
//	printf("%s \n", scene.west_texture);
//	printf("%s \n", scene.east_texture);
//	printf("%s \n", scene.east_texture);
//	printf("Ceiling color: %#X\n", scene.ceiling_color);
//	printf("Floor color: %#X\n", scene.floor_color);
//	printf("oi \n");
//	ok_free("OK OK OK OK OK OK OK OK OK OK OK OK OOOOOOOOOOOKKKKKKKK", &scene);
//}
int	main(int argc, char **argv)
{
	t_cub3d	cub3d;

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
	fill_map_with_zeros(&scene);
	check_map_surrounded(&scene, pos);
	(void)argc;
	(void)argv;
	(void)cub3d;
	printf("Init Cub3d\n");
	cub3d.map = scene.map.map_data;
	init_values(&cub3d);
	init_game(&cub3d);
	finish_game(&cub3d);
	return (EXIT_SUCCESS);
}

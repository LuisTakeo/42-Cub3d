/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaim-yu <tpaim-yu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 21:36:24 by tpaim-yu          #+#    #+#             */
/*   Updated: 2024/10/10 23:35:44 by phraranha        ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/../includes/cub3d.h"

//int	main(int argc, char **argv)
//{
//	t_cub3d	cub3d;
//
//	(void)argc;
//	(void)argv;
//	printf("Init Cub3d\n");
//	init_values(&cub3d);
//	init_game(&cub3d);
//	finish_game(&cub3d);
//	return (EXIT_SUCCESS);
//}

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
	fill_short_lines_with_zeros(&scene);
	check_map_surrounded(&scene, pos);
	ok_free("OK OK OK OK OK OK OK OK OK OK OK OK OOOOOOOOOOOKKKKKKKK", &scene);
}

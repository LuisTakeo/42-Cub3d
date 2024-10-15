/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaim-yu <tpaim-yu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 21:36:24 by tpaim-yu          #+#    #+#             */
/*   Updated: 2024/09/11 21:36:24 by tpaim-yu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int argc, char **argv)
{
	t_cub3d	cub3d;

	(void)argc;
	(void)argv;

	printf("Init Cub3d\n");
	init_values(&cub3d);
	init_game(&cub3d);
	finish_game(&cub3d);
	return (EXIT_SUCCESS);
}
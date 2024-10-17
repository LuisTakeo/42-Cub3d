/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freerror_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaim-yu <tpaim-yu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 01:48:54 by tpaim-yu          #+#    #+#             */
/*   Updated: 2024/10/17 01:48:54 by tpaim-yu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	err(char *str)
{
	ft_putstr_fd("Error\n", STDERR_FILENO);
	ft_putendl_fd(str, STDERR_FILENO);
}

void	err_exit(char *str)
{
	err(str);
	exit(EXIT_FAILURE);
}

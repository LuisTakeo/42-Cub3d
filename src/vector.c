/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaim-yu <tpaim-yu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 20:23:15 by tpaim-yu          #+#    #+#             */
/*   Updated: 2024/10/05 20:23:15 by tpaim-yu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_vector	rotate_vector(t_vector v, float angle)
{
	t_vector	vector;
	float		radians;

	radians = angle * M_PI / 180.0;
	vector.x = v.x * cos(radians) - v.y * sin(radians);
	vector.y = v.x * sin(radians) + v.y * cos(radians);
	return (vector);
}

t_vector	sum_vector(t_vector v, t_vector z)
{
	t_vector	vector;

	vector.x = v.x + z.x;
	vector.y = v.y + z.y;
	return (vector);
}

t_vector	multi_vector(t_vector v, double num)
{
	t_vector	vector;

	vector.x = v.x * num;
	vector.y = v.y * num;
	return (vector);
}

int	update_vector(t_vector *vector, double x, double y)
{
	if (!vector)
		return (EXIT_FAILURE);
	vector->x = x;
	vector->y = y;
	return (EXIT_SUCCESS);
}

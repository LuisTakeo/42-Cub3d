/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaim-yu <tpaim-yu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 22:50:09 by phraranha         #+#    #+#             */
/*   Updated: 2024/10/17 01:39:33 by tpaim-yu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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

int	count_commas(const char *line)
{
	int	count;

	count = 0;
	while (*line)
	{
		if (*line == ',')
			count++;
		line++;
	}
	return (count);
}

bool	rgb_digit(const char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (false);
		str++;
	}
	return (true);
}

int	parse_color(char *line)
{
	char	**color;
	int		r;
	int		g;
	int		b;

	if (count_commas(line) != 2)
		return (err("Color must contain exactly two commas."), EXIT_FAILURE);
	color = ft_split(line, ',');
	if (!color)
		return (err("ft_split"), EXIT_FAILURE);
	if (!validate_color_components(color))
		return (EXIT_FAILURE);
	if (!rgb_digit(color[0]) || !rgb_digit(color[1]) || !rgb_digit(color[2]))
	{
		free_components(color);
		return (err("Color values must contain only digits."), EXIT_FAILURE);
	}
	r = ft_atoi(color[0]);
	g = ft_atoi(color[1]);
	b = ft_atoi(color[2]);
	free_components(color);
	if (!is_valid_color_value(r) || !is_valid_color_value(g)
		|| !is_valid_color_value(b))
		return (err("Color values must be between 0 and 255"), EXIT_FAILURE);
	return (rgb_to_hex(r, g, b));
}

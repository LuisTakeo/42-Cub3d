/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaim-yu <tpaim-yu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 22:50:09 by phraranha         #+#    #+#             */
/*   Updated: 2024/10/17 04:44:32 by tpaim-yu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int32_t	rgb_to_hex(int r, int g, int b)
{
	return ((r << 24) | (g << 16) |(b << 8) | 0xFF);
}

void	hex_to_rgb(int hex, int *r, int *g, int *b)
{
	*r = (hex >> 24) & 0xFF;
	*g = (hex >> 16) & 0xFF;
	*b = (hex >> 8) & 0xFF;
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
		return (err("Color must contain exactly two commas."), -2);
	color = ft_split(line, ',');
	if (!color)
		return (err("ft_split"), -2);
	if (!validate_color_components(color))
		return (-2);
	if (!rgb_digit(color[0]) || !rgb_digit(color[1]) || !rgb_digit(color[2]))
	{
		free_components(color);
		return (err("Color values must contain only digits."), -2);
	}
	r = ft_atoi(color[0]);
	g = ft_atoi(color[1]);
	b = ft_atoi(color[2]);
	free_components(color);
	if (!is_valid_color_value(r) || !is_valid_color_value(g)
		|| !is_valid_color_value(b))
		return (err("Color values must be between 0 and 255"), -2);
	return (rgb_to_hex(r, g, b));
}

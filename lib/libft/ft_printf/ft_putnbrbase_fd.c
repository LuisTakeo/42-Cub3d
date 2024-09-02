/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbrbase_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaim-yu <tpaim-yu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 16:21:04 by tpaim-yu          #+#    #+#             */
/*   Updated: 2024/04/28 16:43:09 by tpaim-yu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_printf.h"

int	ft_putnbrbase(unsigned int n, int is_upper, char *str, int fd)
{
	int				len;
	unsigned int	base_nbr;
	unsigned long	n_long;

	n_long = n;
	base_nbr = ft_strlen(HEX);
	len = 0;
	if (str && is_upper && n_long)
	{
		while (*str)
			len += ft_putchar_fd(ft_toupper(*str++), fd);
	}
	else if (str && n_long)
		len += ft_putstr_fd(str, fd);
	if (n_long >= base_nbr)
		len += ft_putnbrbase(n_long / base_nbr, is_upper, NULL, fd);
	if (is_upper)
		len += ft_putchar_fd(ft_toupper(HEX[n_long % base_nbr]), fd);
	else
		len += ft_putchar_fd(HEX[n_long % base_nbr], fd);
	return (len);
}

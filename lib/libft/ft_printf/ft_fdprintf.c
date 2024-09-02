/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaim-yu <tpaim-yu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 16:17:28 by tpaim-yu          #+#    #+#             */
/*   Updated: 2024/04/28 16:17:28 by tpaim-yu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_printf.h"

static int	ft_filter_to_print_args(int c, va_list args, int fd)
{
	if (c == 'c')
		return (ft_putchar_fd(va_arg(args, int), fd));
	if (c == 's')
		return (ft_putstr_fd(va_arg(args, const char *), fd));
	if (c == 'd' || c == 'i')
		return (ft_putnbr_fd(va_arg(args, int), 0, fd));
	if (c == 'u')
		return (ft_putunsnbr_fd(va_arg(args, unsigned int), fd));
	if (c == 'x')
		return (ft_putnbrbase(va_arg(args, unsigned int), 0, 0, fd));
	if (c == 'X')
		return (ft_putnbrbase(va_arg(args, unsigned int), 1, 0, fd));
	if (c == 'p')
		return (ft_putpointer_fd((unsigned long int) va_arg(args, void *),
				"0x", 0, fd));
	if (c == '%')
		return (ft_putchar_fd('%', fd));
	return (0);
}

static int	ft_print_flags(char c, va_list args, t_flags f, int fd)
{
	if (c == 'd' || c == 'i' || c == 'p')
	{
		if (f.is_plus && (c == 'd' || c == 'i'))
			return (ft_putnbr_fd(va_arg(args, int), '+', fd));
		if (f.is_plus && (c == 'p'))
			return (ft_putpointer_fd((unsigned long int) va_arg(args, void *),
					"0x", '+', fd));
		if (f.is_space && (c == 'd' || c == 'i'))
			return (ft_putnbr_fd(va_arg(args, int), ' ', fd));
		if (f.is_space && (c == 'p'))
			return (ft_putpointer_fd((unsigned long int) va_arg(args, void *),
					"0x", ' ', fd));
		if (c == 'd' || c == 'i')
			return (ft_putnbr_fd(va_arg(args, int), 0, fd));
		if (c == 'p')
			return (ft_putpointer_fd((unsigned long int) va_arg(args, void *),
					"0x", 0, fd));
	}
	if (c == 'X' && (f.is_hash))
		return (ft_putnbrbase(va_arg(args, unsigned int), 1, "0X", fd));
	if (c == 'x' && (f.is_hash))
		return (ft_putnbrbase(va_arg(args, unsigned int), 0, "0x", fd));
	if (c == 's' && (f.is_width))
		return (ft_putstrspc_fd(va_arg(args, char *), f.is_width, fd));
	return (ft_filter_to_print_args(c, args, fd));
}

static void	ft_verify_flags(char flag, t_flags *flags)
{
	if (flag == '+')
		flags->is_plus = 1;
	if (flag == ' ')
		flags->is_space = 1;
	if (flag == '#')
		flags->is_hash = 1;
	if (ft_isdigit(flag))
		flags->is_width = 1;
}

static int	ft_filter_to_print(const char *str, va_list args,
	unsigned int *i, int fd)
{
	t_flags			flags;

	flags = ft_init_flags();
	while (!ft_strchr("cspdiuxX%", str[*i]))
	{
		ft_verify_flags(str[*i], &flags);
		*i = *i + 1;
	}
	return (ft_print_flags(str[*i], args, flags, fd));
}

int	ft_fdprintf(const char *str, int fd, ...)
{
	va_list			args;
	unsigned int	i;
	unsigned int	len;

	if (!str)
		return (-1);
	len = 0;
	i = 0;
	va_start(args, fd);
	while (str[i])
	{
		if (str[i] == '%')
		{
			i++;
			if (ft_strchr("# +", str[i]))
				len += ft_filter_to_print(str, args, &i, fd);
			else
				len += ft_filter_to_print_args(str[i], args, fd);
		}
		else
			len += ft_putchar_fd(str[i], fd);
		i++;
	}
	va_end(args);
	return (len);
}

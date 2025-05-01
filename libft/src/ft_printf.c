/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: w0ffel <w0ffel@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/04 13:44:20 by w0ffel        #+#    #+#                 */
/*   Updated: 2025/01/24 14:56:12 by w0ffel        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printchar(int c)
{
	return (write (1, &c, 1));
}

int	ft_formats(va_list args, const char format)
{
	int	print_length;

	print_length = 0;
	if (format == 'c')
		print_length += ft_printchar(va_arg(args, int));
	else if (format == 's')
		print_length += ft_printstr(va_arg(args, char *));
	else if (format == 'p')
		print_length += ft_print_ptr(va_arg(args, unsigned long long));
	else if (format == 'd' || format == 'i')
		print_length += ft_printnbr(va_arg(args, int));
	else if (format == 'u')
		print_length += ft_print_unsigned(va_arg(args, unsigned int));
	else if (format == 'x' || format == 'X')
		print_length += ft_print_hex(va_arg(args, unsigned int), format);
	else if (format == '%')
		print_length += ft_print_percent();
	return (print_length);
}

int	ft_printf(const char *str, ...)
{
	struct s_vars	vars;
	va_list			args;
	int				temp;

	vars.i = 0;
	vars.print_length = 0;
	if (!str)
		return (-1);
	va_start(args, str);
	while (str[vars.i])
	{
		if (str[vars.i] == '%')
		{
			temp = ft_formats(args, str[vars.i + 1]);
			if (temp == -1)
				return (-1);
			vars.print_length += temp;
			vars.i++;
		}
		else
			vars.print_length += ft_printchar(str[vars.i]);
		vars.i++;
	}
	va_end(args);
	return (vars.print_length);
}

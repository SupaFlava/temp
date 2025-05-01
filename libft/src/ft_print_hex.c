/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_print_hex.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: w0ffel <w0ffel@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/18 14:23:51 by w0ffel        #+#    #+#                 */
/*   Updated: 2025/01/24 15:03:04 by w0ffel        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_hex_length(unsigned int num)
{
	int	length;

	length = 0;
	while (num != 0)
	{
		length++;
		num = num / 16;
	}
	return (length);
}

void	ft_put_hex(unsigned int num, const char format)
{
	if (num >= 16)
	{
		ft_put_hex(num / 16, format);
		ft_put_hex(num % 16, format);
	}
	else
	{
		if (num <= 9)
			ft_putchar_fd((num + '0'), 1);
		else
		{
			if (format == 'x')
				ft_putchar_fd((num - 10 + 'a'), 1);
			if (format == 'X')
				ft_putchar_fd((num - 10 + 'A'), 1);
		}
	}
}

int	ft_print_hex(unsigned int num, const char format)
{
	if (num == 0)
		return (write(1, "0", 1));
	else
		ft_put_hex(num, format);
	return (ft_hex_length(num));
}

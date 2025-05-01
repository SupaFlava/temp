/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_print_unsigned.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: w0ffel <w0ffel@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/18 15:51:05 by w0ffel        #+#    #+#                 */
/*   Updated: 2025/01/24 15:03:11 by w0ffel        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_num_length(unsigned int number)
{
	int	length;

	length = 0;
	while (number != 0)
	{
		length++;
		number = number / 10;
	}
	return (length);
}

char	*ft_uitoa(unsigned int n)
{
	char	*number;
	int		length;

	if (n == 0)
		return (ft_strdup("0"));
	length = ft_num_length(n);
	number = (char *)malloc(sizeof(char) * (length + 1));
	if (!number)
		return (NULL);
	number[length] = '\0';
	while (n != 0)
	{
		number[length - 1] = n % 10 + 48;
		n = n / 10;
		length--;
	}
	return (number);
}

int	ft_print_unsigned(unsigned int n)
{
	int		print_length;
	char	*number;

	print_length = 0;
	if (n == 0)
		return (print_length += write(1, "0", 1));
	else
	{
		number = ft_uitoa(n);
		print_length += ft_printstr(number);
		free(number);
	}
	return (print_length);
}

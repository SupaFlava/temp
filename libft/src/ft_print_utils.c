/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_print_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: w0ffel <w0ffel@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/13 14:20:03 by w0ffel        #+#    #+#                 */
/*   Updated: 2025/01/24 15:03:14 by w0ffel        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int	ft_putstr(char *str)
{
	int	i;
	int	ret;

	i = 0;
	while (str[i])
	{
		ret = write(1, &str[i], 1);
		if (ret < 0)
			return (-1);
		i++;
	}
	return (i);
}

int	ft_printstr(char *str)
{
	if (str == NULL)
	{
		return (ft_putstr("(null)"));
	}
	return (ft_putstr(str));
}

int	ft_printnbr(int nbr)
{
	int		length;
	char	*num;

	length = 0;
	num = ft_itoa(nbr);
	if (!num)
		return (-1);
	length = ft_printstr(num);
	free(num);
	return (length);
}

int	ft_print_percent(void)
{
	return (write(1, "%", 1));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbaetsen <jbaetsen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/16 16:31:37 by jbaetsen      #+#    #+#                 */
/*   Updated: 2025/06/08 15:24:03 by jbaetsen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static unsigned int	ft_numberlength(int num)
{
	unsigned int	len;

	len = 0;
	if (num == 0)
		return (1);
	if (num < 0)
		len += 1;
	while (num != 0)
	{
		num /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char			*string;
	unsigned int	num;
	unsigned int	len;

	len = ft_numberlength(n);
	string = (char *)malloc(sizeof(char) * (len + 1));
	if (string == NULL)
		return (NULL);
	if (n < 0)
	{
		string[0] = '-';
		num = -n;
	}
	else
		num = n;
	if (num == 0)
		string[0] = '0';
	string[len] = '\0';
	while (num != 0)
	{
		string[len - 1] = (num % 10) + '0';
		num = num / 10;
		len--;
	}
	return (string);
}

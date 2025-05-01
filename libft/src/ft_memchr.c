/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbaetsen <jbaetsen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/11 16:22:58 by jbaetsen      #+#    #+#                 */
/*   Updated: 2024/10/24 11:52:28 by jbaetsen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memchr(const void *str, int c, size_t n)
{
	size_t				i;
	const unsigned char	*s;

	i = 0;
	s = (const unsigned char *)str;
	while (i < n)
	{
		if (s[i] == (unsigned char)c)
		{
			return ((void *)&s[i]);
		}
		i++;
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbaetsen <jbaetsen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/09 16:56:39 by jbaetsen      #+#    #+#                 */
/*   Updated: 2024/10/24 11:34:46 by jbaetsen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strchr(const char	*str, int c)
{
	unsigned int	i;
	unsigned char	ch;

	i = 0;
	ch = (unsigned char)c;
	while (str[i] != '\0')
	{
		if ((unsigned char)str[i] == ch)
		{
			return ((char *)&str[i]);
		}
		i++;
	}
	if (ch == '\0')
	{
		return ((char *)&str[i]);
	}
	return (NULL);
}

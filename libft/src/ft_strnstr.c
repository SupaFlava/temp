/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnstr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbaetsen <jbaetsen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/11 17:19:28 by jbaetsen      #+#    #+#                 */
/*   Updated: 2024/10/24 11:38:17 by jbaetsen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strnstr(const char *string, const char *substring, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (*substring == '\0')
		return ((char *)string);
	while (i < len && string[i] != '\0')
	{
		if (string[i] == substring[0])
		{
			j = 0;
			while (substring[j] != '\0' && (i + j) < len
				&& string[i + j] == substring[j])
			{
				j++;
			}
			if (substring[j] == '\0')
			{
				return ((char *)&string[i]);
			}
		}
		i++;
	}
	return (NULL);
}

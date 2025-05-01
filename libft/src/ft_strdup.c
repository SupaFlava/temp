/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbaetsen <jbaetsen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/14 16:17:38 by jbaetsen      #+#    #+#                 */
/*   Updated: 2024/10/24 12:24:18 by jbaetsen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	size_t	len;
	char	*dest;

	len = ft_strlen(src);
	dest = (char *)malloc(len + 1);
	if (src == NULL || dest == NULL)
	{
		return (NULL);
	}
	ft_strlcpy(dest, src, len + 1);
	return (dest);
}

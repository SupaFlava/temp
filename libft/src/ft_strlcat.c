/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcat.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbaetsen <jbaetsen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/09 15:04:37 by jbaetsen      #+#    #+#                 */
/*   Updated: 2024/10/24 11:35:48 by jbaetsen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	srclen;
	size_t	destlen;
	size_t	i;

	srclen = 0;
	destlen = 0;
	i = 0;
	while (dest[destlen] && destlen < size)
		destlen++;
	while (src[srclen])
		srclen++;
	if (size <= destlen)
		return (srclen + size);
	while (src[i] && (destlen + i) < (size - 1))
	{
		dest[destlen + i] = src[i];
		i++;
	}
	if (destlen < size)
		dest[destlen + i] = '\0';
	return (srclen + destlen);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   str_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmhazres <rmhazres@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/08 12:12:21 by jbaetsen      #+#    #+#                 */
/*   Updated: 2025/05/16 12:25:59 by jbaetsen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*ft_strdup_s(t_mshell *shell, const char *src) //mallocs into the struct.
{
	size_t	len;
	char	*dest;

	len = ft_strlen(src);
	dest = (char *)ft_malloc_s(shell, len + 1, MEM_TEMP);
	if (src == NULL || dest == NULL)
	{
		return (NULL);
	}
	ft_strlcpy(dest, src, len + 1);
	return (dest);
}

char	*ft_strndup(t_mshell *shell, const char *str, size_t n)
{
	size_t	len;
	char	*dup;

	len = 0;
	while (str[len] && len < n)
		len++;
	dup = (char *)ft_malloc_s(shell,(len + 1), MEM_TEMP);
	if (!dup)
		return (NULL);
	len = 0;
	while (str[len] && len < n)
	{
		dup[len] = str[len];
		len++;
	}
	dup[len] = '\0';
	return (dup);
}

char	*ft_strcpy(char *dst, const char *src)
{
	size_t	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

int	ft_strcmp(const char *str1, const char *str2)
{
	size_t	i;

	i = 0;
	while (str1[i] && str2[i] && str1[i] == str2[i])
		i++;
	return ((unsigned char)str1[i] - (unsigned char) str2[i]);
}

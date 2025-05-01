/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbaetsen <jbaetsen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/15 12:58:20 by jbaetsen      #+#    #+#                 */
/*   Updated: 2024/10/24 11:56:09 by jbaetsen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	size_t	trimlen;
	char	*trimmed;

	start = 0;
	end = ft_strlen(s1);
	if (!s1 || !set)
	{
		return (NULL);
	}
	while (s1[start] && ft_strchr(set, s1[start]))
	{
		start++;
	}
	while (end > start && ft_strchr(set, s1[end - 1]))
	{
		end--;
	}
	trimlen = end - start;
	trimmed = malloc(trimlen + 1);
	if (!trimmed)
		return (NULL);
	ft_strlcpy(trimmed, s1 + start, trimlen + 1);
	return (trimmed);
}

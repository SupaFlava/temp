/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmhazres <rmhazres@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 12:12:21 by jbaetsen          #+#    #+#             */
/*   Updated: 2025/07/02 14:12:28 by rmhazres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*ft_strdup_s(t_mshell *shell, const char *src, t_mem_t type)
{
	size_t	len;
	char	*dest;

	len = ft_strlen(src);
	dest = (char *)ft_malloc_s(shell, len + 1, type);
	if (src == NULL || dest == NULL)
	{
		return (NULL);
	}
	ft_strlcpy(dest, src, len + 1);
	return (dest);
}

char	*ft_strndup_s(t_mshell *shell, const char *str, size_t n, t_mem_t type)
{
	size_t	len;
	char	*dup;

	len = 0;
	while (str[len] && len < n)
		len++;
	dup = (char *)ft_malloc_s(shell, (len + 1), type);
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

int	ft_strcmp(const char *str1, const char *str2)
{
	size_t	i;

	i = 0;
	while (str1[i] && str2[i] && str1[i] == str2[i])
		i++;
	return ((unsigned char)str1[i] - (unsigned char) str2[i]);
}

char	*ft_substr_s(t_mshell *shell, char const *s, unsigned b, size_t len)
{
	char	*new;
	size_t	slen;
	size_t	finish;

	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	if (b >= slen)
		return (ft_strdup_s(shell, "", MEM_LONG));
	finish = slen - b;
	if (b < slen)
		finish = slen - b;
	if (finish > len)
		finish = len;
	new = ft_malloc_s(shell, sizeof(char) * (finish + 1), MEM_LONG);
	if (!new)
		return (0);
	ft_strlcpy(new, s + b, finish +1);
	return (new);
}

char	*ft_strjoin_s(char const *s1, char const *s2, t_mshell *sh, t_mem_t t)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	str = ft_malloc_s(sh,
			sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1), t);
	if (!str)
		return (NULL);
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}

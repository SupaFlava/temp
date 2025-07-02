/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_two_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmhazres <rmhazres@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 14:49:32 by jbaetsen          #+#    #+#             */
/*   Updated: 2025/07/02 14:12:13 by rmhazres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*ft_itoa_s(t_mshell *shell, int n, t_mem_t type)
{
	char			*string;
	unsigned int	num;
	unsigned int	len;

	len = ft_numberlength(n);
	string = (char *)ft_malloc_s(shell, sizeof(char) * (len + 1), type);
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

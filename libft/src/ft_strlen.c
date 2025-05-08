/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlen.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbaetsen <jbaetsen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/08 12:35:12 by jbaetsen      #+#    #+#                 */
/*   Updated: 2025/05/08 16:50:16 by jbaetsen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

size_t	ft_strlen(const char *str)
{
	size_t	i;
	if (!str)
		return (0);
		
	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_bzero.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbaetsen <jbaetsen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/08 14:56:56 by jbaetsen      #+#    #+#                 */
/*   Updated: 2024/10/24 11:45:28 by jbaetsen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_bzero(void *ptr, size_t n)
{
	unsigned char	*p;

	if (n == 0)
		return (ptr);
	p = (unsigned char *)ptr;
	ft_memset(p, 0, n);
	return (ptr);
}

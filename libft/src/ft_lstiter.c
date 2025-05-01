/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstiter.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: w0ffel <w0ffel@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/26 16:13:19 by w0ffel        #+#    #+#                 */
/*   Updated: 2024/10/28 17:52:18 by w0ffel        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*temp;

	temp = lst;
	while (temp)
	{
		f(temp->content);
		temp = temp->next;
	}
}

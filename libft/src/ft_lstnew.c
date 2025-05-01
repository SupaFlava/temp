/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_listnew.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: w0ffel <w0ffel@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/26 15:39:31 by w0ffel        #+#    #+#                 */
/*   Updated: 2024/10/26 15:44:21 by w0ffel        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}

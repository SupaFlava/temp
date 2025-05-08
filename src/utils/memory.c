/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmhazres <rmhazres@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 14:10:03 by rmhazres          #+#    #+#             */
/*   Updated: 2025/05/08 11:54:14 by rmhazres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_malloc_s(t_mshell *shell,size_t size , t_alloc_type type)
{
	void	 *ptr;
	t_alloc	 *node;
	
	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	node = malloc (sizeof(t_alloc));
	if (!node)
	{
		free(ptr);
		return (NULL);
	}
	node->ptr = ptr;
	node->next = (NULL);
	if (type == MEM_TEMP)
		ft_lstadd_back(shell->temp_allocs, ptr);
	else if (type == MEM_LONG)
		ft_lstadd_back(shell->long_allocs, ptr);
	return (ptr);
}

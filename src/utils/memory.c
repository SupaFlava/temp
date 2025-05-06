/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmhazres <rmhazres@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 14:10:03 by rmhazres          #+#    #+#             */
/*   Updated: 2025/05/06 15:08:06 by rmhazres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_malloc_s(t_mshell shell,size_t size)
{
	t_list *new_node;
	void	 *ptr;
	
	ptr = malloc(sizeof(size));
	if (!ptr)
		return NULL;
	
	new_node  = malloc(sizeof(t_list));
	if (!new_node)
	{
		free(ptr);	
		return NULL;
	}
	new_node->ptr = ptr;
	new_node->next = shell.mem_list;
	shell.mem_list = new_node;
	return (ptr);
}

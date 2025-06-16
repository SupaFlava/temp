/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmhazres <rmhazres@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 14:10:03 by rmhazres          #+#    #+#             */
/*   Updated: 2025/06/16 14:00:23 by rmhazres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_arr(char **arr)
{
	int i;

	i = 0;
	if(!arr)
		return;
	while(arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	arr = NULL;
}
void	ft_free(t_mshell *shell, t_mem_t type)
{
	if (type == MEM_TEMP)
	{
		ft_lstclear(&shell->temp_allocs, free);
		shell->temp_allocs = NULL;
	}
	if (type == MEM_LONG)
	{
		ft_lstclear(&shell->long_allocs, free);
		shell->long_allocs = NULL;
	}

}

void	*ft_malloc_s(t_mshell *shell, size_t size, t_mem_t type)
{
	void	*ptr;
	t_list	*node;

	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	node = malloc (sizeof(t_alloc));
	if (!node)
	{
		free(ptr);
		return (NULL);
	}
	node->content = ptr;
	node->next = (NULL);
	if (type == MEM_TEMP)
		ft_lstadd_back(&shell->temp_allocs, node);
	else if (type == MEM_LONG)
		ft_lstadd_back(&shell->long_allocs, node);
	return (ptr);
}

void free_env(t_env *node)
{
	ft_printf("deleting %s \n", node->key);

	(void)node;
}

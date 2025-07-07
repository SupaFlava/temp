/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmhazres <rmhazres@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 14:10:03 by rmhazres          #+#    #+#             */
/*   Updated: 2025/07/07 12:35:20 by rmhazres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	debug_alloc_list(t_list *lst)
{
	int i = 0;
	while (lst)
	{
		ft_printf("ALLOC[%d] = %p\n", i++, lst->content);
		lst = lst->next;
	}
}

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	arr = NULL;
}

void	ft_free(t_mshell *shell, t_mem_t type)
{
	if (shell->line)
		free(shell->line);
	if (shell->commands && shell->commands->heredoc_temp)
		unlink(shell->commands->heredoc_temp);
	shell->line = NULL;
	if (type == MEM_TEMP)
	{
		ft_lstclear(&shell->temp_allocs, free);
		shell->temp_allocs = NULL;
		shell->tokens = NULL;
		shell->commands = NULL;
	}
	if (type == MEM_LONG)
	{
		ft_lstclear(&shell->long_allocs, free);
		shell->long_allocs = NULL;
		shell->env_list = NULL;
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

void	free_env(t_env *env)
{
	t_env *tmp;

	while (env)
	{
		tmp = env->next;
		if (env->key)
			free(env->key);
		if (env->value)
			free(env->value);
		free(env);
		env = tmp;
	}
}

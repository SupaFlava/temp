/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmhazres <rmhazres@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:39:02 by rmhazres          #+#    #+#             */
/*   Updated: 2025/06/30 16:21:55 by rmhazres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_add_back(t_env **head, t_env *new_node)
{
	t_env	*tmp;

	if (!head || !new_node)
		return ;
	if (*head == NULL)
	{
		*head = new_node;
		return ;
	}
	tmp = *head;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new_node;
}

void	env_print(t_mshell *shell)
{
	t_env	*temp;

	temp = shell->env_list;
	while (temp != NULL)
	{
		if (temp->key != NULL && temp->value != NULL)
		{
			ft_putstr_fd(temp->key, STDOUT_FILENO);
			ft_putstr_fd("=", STDOUT_FILENO);
			ft_putstr_fd(temp->value, STDOUT_FILENO);
			ft_putchar_fd('\n', STDOUT_FILENO);
		}
		temp = temp->next;
	}
}

t_env	*get_env(t_env *env, char *key)
{
	t_env	*result;
	t_env	*temp_env;

	temp_env = env;
	while (temp_env)
	{
		if (ft_strcmp(temp_env->key, key) == 0)
		{
			result = temp_env;
			return (result);
		}
		temp_env = temp_env->next;
	}
	return (NULL);
}

int	set_env(t_mshell *shell, char *key, char *value)
{
	t_env	*temp;

	temp = shell->env_list;
	while (temp)
	{
		if (ft_strcmp(temp->key, key) == 0)
		{
			temp->value = ft_strdup_s(shell ,value, MEM_LONG);
			return (EXIT_SUCCESS);
		}
		temp = temp->next;
	}
	return (EXIT_FAILURE);
}

int	delete_env(t_env **list, t_env *node)
{
	t_env	*prev;
	t_env	*current;

	if (*list == node)
	{
		*list = node->next;
		return (1);
	}
	else
	{
		prev = *list;
		current = (*list)->next;
	}
	while (current)
	{
		if (current == node)
		{
			prev->next = current->next;
			return (1);
		}
		prev = current;
		current = current->next;
	}
	return (0);
}

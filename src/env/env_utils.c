/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmhazres <rmhazres@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:39:02 by rmhazres          #+#    #+#             */
/*   Updated: 2025/05/16 13:08:03 by rmhazres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    env_add_back(t_env **head, t_env *new_node)
{
    t_env *tmp;
    
    if (!head || !new_node)
        return;
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

void env_print(t_mshell *shell)
{
	t_env *temp;
	
	temp = shell->env_list;


	while (temp != NULL)
	{
		if (temp->key != NULL)
			ft_printf("%s=",temp->key);
		if (temp->value != NULL)
			ft_printf("%s\n",temp->value);
		temp = temp->next;
	}
}
char *get_env(t_env *env , char *key)
{
	char *path;
	t_env *temp_env;

	temp_env = env;
	while(temp_env)
	{
		if (ft_strcmp(temp_env->key, key) == 0)
		{
			path = temp_env->value;
			return (path);
		}
		temp_env = temp_env->next;
	}
	return(NULL);
}
int	set_env(t_env *env, char *key, char *value)
{
	t_env *temp;

	temp = env;
	while (temp)
	{
		if (ft_strcmp(temp->key, key) == 0)
			{
				temp->value = value;
				return (EXIT_SUCCESS);
			}
		temp = temp->next;
		}
		return (EXIT_FAILURE);
	}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_list.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmhazres <rmhazres@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/03 14:20:30 by rmhazres      #+#    #+#                 */
/*   Updated: 2025/06/17 15:27:53 by jbaetsen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_env(t_env *env)
{
	int i;

	i = 0;
	while(env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

int env_add(t_mshell *shell, char *key, char *value)
{
    t_env *new_node;

    new_node = ft_malloc_s(shell ,sizeof(t_env), MEM_LONG);
    if (!new_node)
       return(EXIT_FAILURE);
    new_node->key = key;
	ft_printf("");
    new_node->value = value;
    new_node->next = NULL;
    if (shell->env_list == NULL)
    {
        shell->env_list = new_node;
        return (EXIT_SUCCESS);
    }
    env_add_back(&shell->env_list, new_node);
    return (EXIT_SUCCESS);
}

int  init_env(t_mshell *shell ,char **envp)
{
    char *key;
    char *value;
    char *equal;

    while(*envp)
    {
        equal = ft_strchr(*envp,'=');
        if (!equal)
            return (EXIT_FAILURE);
        key = ft_substr_s(shell,*envp, 0, equal - *envp);
        value = ft_strdup_s(shell ,equal + 1, MEM_LONG);
        env_add(shell, key, value);
        envp++;
    }
    return (0);
}

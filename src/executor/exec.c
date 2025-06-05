/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmhazres <rmhazres@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:23:04 by rmhazres          #+#    #+#             */
/*   Updated: 2025/06/05 11:25:41 by rmhazres         ###   ########.fr       */
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

char **env_to_envp(t_mshell *shell)
{
	t_env *temp;
	char *joinded;
	int count;
	int i;
	char **envp;
	
	temp = shell->env_list;
	count =  count_env(temp);
	envp = ft_malloc_s(shell,sizeof(char *)* (count + 1), MEM_TEMP);
	i = 0;
	while(temp)
	{
		joinded = ft_strjoin(temp->key, "=");
		envp[i++] = ft_join_and_free(joinded, temp->value);
		i++;
		temp = temp->next;
	}
	envp[i] = NULL;
	return (envp);
}

int check_exec(t_command *cmd, t_mshell *shell)
{
	char **envp;

	 envp = env_to_envp(shell);
	
	if(ft_strchr(cmd->args[0], '/') != NULL)
	{
		printf("in here");
		execve(cmd->args[0],cmd->args ,envp);
	}
	else
	{
		printf("no exec\n");
	}
	return (0);
}

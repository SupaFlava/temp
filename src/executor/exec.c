/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmhazres <rmhazres@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:23:04 by rmhazres          #+#    #+#             */
/*   Updated: 2025/06/04 14:26:40 by rmhazres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_env(t_env *env)
{
	int i;

	i = 0;
	while(env->next != NULL)
	{
		i++;
		env = env->next;
	}
	return (i);
}

char *env_to_envp(t_mshell *shell)
{
	t_env *temp;
	
	int count;
	int i;

	count =  count_env(&shell->env_list);
	char **envp;
	
	envp = ft_malloc_s(shell,count, MEM_TEMP);
	temp = shell->env_list;
	while(temp)
	{
		
	}
}



int check_exec(t_command *cmd, t_mshell *shell)
{
	char **envp;

	env_to_envp(shell);
	
	if(ft_strchr(cmd->args[0], '/') != NULL)
	{
		printf("in here");
		execve(cmd->args[0],cmd->args ,envl);
	}
	else
	{
		printf("no exec\n");
	}
	return (0);
}

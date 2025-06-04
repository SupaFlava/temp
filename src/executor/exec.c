/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmhazres <rmhazres@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:23:04 by rmhazres          #+#    #+#             */
/*   Updated: 2025/06/04 14:38:57 by rmhazres         ###   ########.fr       */
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

char *env_to_envp(t_mshell *shell)
{
	t_env *temp;
	
	int count;
	int i;
	
	temp = shell->env_list;

	count =  count_env(temp);
	char **envp;	
	envp = ft_malloc_s(shell,sizeof(char *)* (count + 1), MEM_TEMP);
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

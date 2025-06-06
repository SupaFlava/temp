/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmhazres <rmhazres@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:23:04 by rmhazres          #+#    #+#             */
/*   Updated: 2025/06/06 14:07:28 by rmhazres         ###   ########.fr       */
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

static int is_executable(const char *path)
{
	struct stat st;
	
	if (stat(path, &st) < 0)
		return 0;
	if (!S_ISREG(st.st_mode))
		return (0);
	if (access(path,X_OK) < 0)
	{
		return (0);
	}
	return (1);
}
char **env_to_envp(t_mshell *shell)
{
	t_env *temp;
	char *joined;
	int count;
	int i;
	char **envp;
	
	temp = shell->env_list;
	count =  count_env(temp);
	envp = ft_malloc_s(shell,sizeof(char *)* (count + 1), MEM_TEMP);
	if(!envp)
		return (NULL);
	i = 0;
	while(temp)
	{
		joined = ft_strjoin(temp->key, "=");
		if (!joined)
			return(free_arr(envp),NULL);
		envp[i] = ft_join_and_free(joined, temp->value);
		if(!envp[i])
			return (free_arr(envp),NULL);
		i++;
		temp = temp->next;
	}
	envp[i] = NULL;
	return (envp);
}

char *find_in_path(char *arg, t_env *env_lst)
{
	t_env *temp;
	char **env_arr;
	char *joined;
	char *path;
	int	i;
	
	temp = get_env(env_lst,"PATH");
	if (!temp)
		return (ft_printf("bash: %s: PATH not set\n", arg), NULL);
	env_arr = ft_split(temp->value,':');
	if(!env_arr)
		return (NULL);
	i = 0;
	while(env_arr[i])
	{
		joined = ft_strjoin(env_arr[i],"/");
		path = ft_join_and_free(joined, arg);
		if(is_executable(path))
			return (free_arr(env_arr),path);
		free(path);
		i++;
	}
	free_arr(env_arr);
	return (NULL);
}

int check_exec(t_command *cmd, t_mshell *shell)
{
	char **envp;
	char *path;

	if(!cmd || !cmd->args || !cmd->args[0])
		return (1);
	envp = env_to_envp(shell);
	if(!envp)
		return(-1);
	if(ft_strchr(cmd->args[0], '/') != NULL)
	{
		if (!is_executable(cmd->args[0]))
		{
			if(access(cmd->args[0],F_OK )< 0)
				ft_printf("bash: %s No such file or directory\n", cmd->args[0]);
			else if (errno == EACCES)
				ft_printf("bash: %s Permission denied\n", cmd->args[0]);
			else
                ft_printf("command:'%s' not found \n", cmd->args[0]);
			free_arr(envp);
			return (1);
		}
		execve(cmd->args[0],cmd->args ,envp);
		ft_printf("bash: %s: %s\n", cmd->args[0], strerror(errno));
        free_arr(envp);
        return 1;
	}
	else
	{
		path =	find_in_path(cmd->args[0],shell->env_list);
		if(!path)
		{
			ft_printf("bash: %s No such file or directory\n", cmd->args[0]);
			free_arr(envp);
			return (1);
		}
		execve(path,cmd->args, envp);
		ft_printf("bash: %s: %s\n", path, strerror(errno));
		free(path);
		free_arr(envp);
	}
	return (0);
}

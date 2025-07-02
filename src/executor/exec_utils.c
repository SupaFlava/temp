/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmhazres <rmhazres@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 13:57:38 by rmhazres          #+#    #+#             */
/*   Updated: 2025/07/02 13:39:38 by rmhazres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_executable(const char *path)
{
	struct stat	st;

	if (stat(path, &st) < 0)
		return (0);
	if (!S_ISREG(st.st_mode))
		return (0);
	if (access(path, X_OK) < 0)
		return (0);
	return (1);
}

char	**env_to_envp(t_mshell *shell)
{
	t_env	*temp;
	char	*joined;
	int		count;
	int		i;
	char	**envp;

	temp = shell->env_list;
	count = count_env(temp);
	envp = ft_malloc_s(shell, sizeof(char *) * (count + 1), MEM_TEMP);
	if (!envp)
		return (NULL);
	i = 0;
	while (temp)
	{
		joined = ft_strjoin(temp->key, "=");
		if (!joined)
			return (free_arr(envp), NULL);
		envp[i] = ft_join_and_free(joined, temp->value);
		if (!envp[i])
			return (free_arr(envp), NULL);
		i++;
		temp = temp->next;
	}
	envp[i] = NULL;
	return (envp);
}

char	*find_in_path(char *arg, t_env *env_lst)
{
	t_env	*temp;
	char	**env_arr;
	char	*joined;
	char	*path;
	int		i;

	temp = get_env(env_lst, "PATH");
	if (!temp)
		return (print_err("minishell", arg, "PATH not set\n"), NULL);
	env_arr = ft_split(temp->value, ':');
	if (!env_arr)
		return (NULL);
	i = 0;
	while (env_arr[i])
	{
		joined = ft_strjoin(env_arr[i], "/");
		path = ft_join_and_free(joined, arg);
		if (is_executable(path))
			return (free_arr(env_arr), path);
		free(path);
		i++;
	}
	free_arr(env_arr);
	return (NULL);
}

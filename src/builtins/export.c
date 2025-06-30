/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmhazres <rmhazres@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:19:39 by rmhazres          #+#    #+#             */
/*   Updated: 2025/06/30 13:44:10 by rmhazres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_export(char *str)
{
	int	i;

	i = 0;
	if (!str || str[0] == '=')
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

char	**sort_env(char **envp)
{
	char	*temp;
	int		count;
	int		i;
	int		j;

	count = 0;
	while (envp[count])
		count ++;
	i = 0;
	while (i < count -1)
	{
		j = 0;
		while (j < count - i - 1)
		{
			if (ft_strcmp(envp[j], envp[j + 1]) > 0)
			{
				temp = envp[j];
				envp[j] = envp[j + 1];
				envp[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
	return (envp);
}

void	print_export_env(t_mshell *shell)
{
	char	**envp;
	int		i;

	envp = env_to_envp(shell);
	sort_env(envp);
	i = 0;
	while (envp[i])
	{
		ft_putstr_fd("declare -x ", STDERR_FILENO);
		ft_putstr_fd(envp[i], STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		i++;
	}
}

int	builtin_export(t_mshell *shell, char **args)
{
	int	i;

	if (count_args(args) == 1)
		return (print_export_env(shell), 0);
	i = 1;
	while (args[i])
	{
		if (!is_valid_export(args[i]))
		{
			print_err("bash: export", args[i], "not a valid identifier");
			return (EXIT_FAILURE);
		}
		init_env(shell, &args[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}

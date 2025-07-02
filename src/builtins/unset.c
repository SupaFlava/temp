/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmhazres <rmhazres@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 13:10:36 by rmhazres          #+#    #+#             */
/*   Updated: 2025/07/02 14:30:05 by rmhazres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_identifier(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	builtin_unset(t_mshell *shell, char **args)
{
	t_env	*node;
	int		i;
	int		status;

	i = 1;
	status = 0;
	if (!shell->env_list)
		return (0);
	while (args[i])
	{
		if (!is_valid_identifier(args[i]))
		{
			print_err("unset", args[i], "not a valid identifier");
			status = 1;
		}
		else
		{
			node = get_env(shell->env_list, args[i]);
			if (node)
				delete_env(&shell->env_list, node);
		}
		i++;
	}
	return (status);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmhazres <rmhazres@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 13:10:36 by rmhazres          #+#    #+#             */
/*   Updated: 2025/06/30 14:45:34 by rmhazres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (!is_valid_export(args[i]))
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

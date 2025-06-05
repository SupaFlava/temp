/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmhazres <rmhazres@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 13:10:36 by rmhazres          #+#    #+#             */
/*   Updated: 2025/05/24 11:45:27 by rmhazres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_unset(t_mshell *shell, char **args)
{
	t_env *node;

	if (!shell->env_list)
		return (0);
	node = get_env(shell->env_list , args[1]);
	if (!node)
		return (0);
	delete_env(&shell->env_list, node);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmhazres <rmhazres@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 15:47:17 by jbaetsen          #+#    #+#             */
/*   Updated: 2025/07/07 17:39:56 by rmhazres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*expand_env(t_mshell *shell, char *key)
{
	t_env	*expanded;

	expanded = get_env(shell->env_list, key);
	if (!expanded)
	{
		expanded = ft_malloc_s(shell, sizeof(t_env), MEM_LONG);
		if (!expanded)
			return (NULL);
		expanded->key = ft_strdup_s(shell, key, MEM_LONG);
		expanded->value = ft_strdup_s(shell, "", MEM_LONG);
		expanded->next = NULL;
		printf("exend  key is %s\n", expanded->key);
		printf("exend  valiue is %s\n", expanded->value);
	}
	return (expanded);
}

void	finalize_command(t_parser *p)
{
	t_command	*last;

	if (!p->current_cmd)
		return ;
	last = p->cmd_list;
	if (!last)
	{
		p->cmd_list = p->current_cmd;
		return ;
	}
	while (last-> next)
		last = last->next;
	if (last != p->current_cmd)
		last->next = p->current_cmd;
}

int	add_arg_to_cmd(t_mshell *shell, t_command *command, char *arg)
{
	int		i;
	int		j;
	char	**new_args;

	i = 0;
	if (!arg || arg[0] == '\0')
		return (2);
	while (command->args && command->args[i])
		i++;
	new_args = ft_malloc_s(shell, sizeof(char *) * (i + 2), MEM_TEMP);
	if (!new_args)
		return (0);
	j = 0;
	while (j < i)
	{
		new_args[j] = command->args[j];
		j++;
	}
	new_args[i] = ft_strdup_s(shell, arg, MEM_TEMP);
	new_args[i + 1] = NULL;
	command->args = new_args;
	return (1);
}

void	process_input(t_mshell *shell)
{
	shell->tokens = lexer(shell);
	if (!shell->tokens)
		return ;
	if (shell->tokens)
	{
		//print_tokens(shell->tokens); //remove before handin
		shell->commands = parser(shell);
		if (!shell->commands)
			return ;
		// else
		// 	print_command(shell->commands); //remove before handin
	}
}

char	*read_input(void)
{
	char	*line;

	line = readline("( ͡° ͜ʖ ͡°) ");
	if (!line)
		return (NULL);
	return (line);
}

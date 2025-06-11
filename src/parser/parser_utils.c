/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmhazres <rmhazres@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/02 15:47:17 by jbaetsen      #+#    #+#                 */
/*   Updated: 2025/06/10 22:42:19 by jbaetsen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	add_arg_to_cmd(t_mshell *shell, t_command *command, char *arg)
{
	int		i;
	int		j;
	char	**new_args;

	i = 0;
	while (command->args && command->args[i])
		i++;
	new_args = ft_malloc_s(shell, sizeof(char *) * (i + 2), MEM_TEMP);
	if (!new_args)
		return ;
	j = 0;
	while (j < i)
	{
		new_args[j] = command->args[j];
		j++;
	}
	new_args[i] = ft_strdup_s(shell, arg, MEM_TEMP);
	new_args[i + 1] = NULL;
	command->args = new_args;
}

void	init_parser(t_mshell *shell, t_parser *p)
{
	p->current_token = shell->tokens;
	p->cmd_list = NULL;
	p->current_cmd = NULL;
	p->state = PARSE_DEFAULT;
	p->env = shell->env_list;
	p->exit_value = ft_itoa_s(shell, shell->exit_status, MEM_LONG);
}

void	process_input(t_mshell *shell)
{
	shell->tokens = lexer(shell);
	if (!shell->tokens)
	{
		ft_printf("no tokens found\n");
		return ;
	}
	if (shell->tokens)
	{
		print_tokens(shell->tokens);
		shell->commands = parser(shell);
		if (!shell->commands)
		{
			ft_printf("no commands found\n");
			return ;
		}
		else
			print_commands(shell->commands);
	}
}

char	*read_input(void)
{
	char	*line;

	line = readline("> ");
	if (!line)
	{
		ft_printf("exiting minishell\n");
		exit(0);
	}
	return (line);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmhazres <rmhazres@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/02 15:47:17 by jbaetsen      #+#    #+#                 */
/*   Updated: 2025/05/28 00:18:06 by jbaetsen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_builtin(t_token *token, t_command *command)
{
	if (!ft_strcmp(token->content, "echo")
		|| !ft_strcmp(token->content, "cd")
		|| !ft_strcmp(token->content, "pwd")
		|| !ft_strcmp(token->content, "export")
		|| !ft_strcmp(token->content, "unset")
		|| !ft_strcmp(token->content, "env")
		|| !ft_strcmp(token->content, "exit"))
		command->is_builtin = 1;
}

int		parse_nonredir_token(t_mshell *shell, t_token *token, t_command *command)
{
	if (token->type == TOK_WORD
		|| token->type == TOK_ENV_VAR
		|| token->type == TOK_EXIT_STATUS
		|| token->type == TOK_QUOTED)
	{
		if (token->type == TOK_WORD && command->args == NULL)
			check_builtin(token, command);
		if (append_to_args(shell,command, token->content))
			return (1);
	}

	return (0);
}

int	parse_redir_token(t_mshell *shell, t_token *token, t_command *command)
{
	if (token->type == TOK_REDIR_IN
		|| token->type == TOK_REDIR_OUT
		|| token->type == TOK_APPEND
		|| token->type == TOK_HEREDOC)
	{
		if (!token->next || (token->next->type != TOK_WORD && token->next->type != TOK_QUOTED))
		{
			ft_printf("SYNTAX ERROR invalid token after redir\n");
			return (1);
		}
		else
		{
			if (token->type == TOK_REDIR_IN || token->type == TOK_HEREDOC)
				command->infile = ft_strdup_s(shell, token->next->content, MEM_TEMP);
			if (token->type == TOK_REDIR_OUT || token->type == TOK_APPEND)
				command->outfile = ft_strdup_s(shell, token->next->content, MEM_TEMP);
		}
	}
	return (0);
}

t_command	*create_command(t_mshell *shell)
{
	t_command	*command;

	command = ft_malloc_s(shell,(sizeof(t_command)),MEM_TEMP);
	if (!command)
		return (NULL);
	command->args = NULL;
	command->infile = NULL;
	command->outfile = NULL;
	command->append = 0;
	command->is_builtin = 0;
	command->next = NULL;
	return (command);
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

#include  "minishell.h"



t_command	*parse_tokens_to_cmds(t_mshell *shell)
{
	t_token		*token;
	t_command	*command;
	t_command	*head;

	token = shell->tokens;

	command = create_command(shell);
	head = command;
	while (token && token->type != TOK_PIPE)
	{
		if (parse_redir_token(shell, token, command))
			return (NULL);
		if (parse_nonredir_token(shell, token, command))
			return (NULL);

		token = token->next;
	}
	if (token != NULL && token->type == TOK_PIPE)
	{
		token = token->next;
		command->next = create_command(shell);
		command = command->next;
		while (token && token->type != TOK_PIPE)
		{
			if (parse_redir_token(shell, token, command))
				return (NULL);
			if (parse_nonredir_token(shell, token, command))
				return (NULL);

			token = token->next;
		}

	}
	return (head);
}

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

#include "lexer.h"

//in case we stil want to test things we might need these functions

void	print_tokens(t_token *tokens)
{
	while (tokens)
	{
		ft_printf("Token: %s | type: %s | quote_group: %d\n",
			(char *)tokens->content,
			token_type_to_string(tokens->type),
			tokens->quote_id);
		tokens = tokens->next;
	}
}

void	print_command(t_command *cmd)
{
	int	i;
	t_redir	*redir;

	int	cmd_index = 0;
	while (cmd)
	{
		ft_printf("=== Command %d ===\n", cmd_index);

		// Print arguments
		ft_printf("Arguments:\n");
		if (cmd->args)
		{
			for (i = 0; cmd->args[i]; i++)
				ft_printf("  arg[%d]: %s\n", i, cmd->args[i]);
		}
		else
			ft_printf("  (none)\n");

		// Print infile redirections
		ft_printf("Infile(s):\n");
		redir = cmd->infile;
		if (!redir)
			ft_printf("  (none)\n");
		while (redir)
		{
			ft_printf("  %s\n", redir->file);
			redir = redir->next;
		}

		// Print outfile redirections
		ft_printf("Outfile(s):\n");
		redir = cmd->outfile;
		if (!redir)
			ft_printf("  (none)\n");
		while (redir)
		{
			ft_printf("  %s\n", redir->file);
			redir = redir->next;
		}

		// Print redirection & heredoc flags
		ft_printf("Append: %s\n", cmd->append ? "true" : "false");
		ft_printf("Heredoc: %s\n", cmd->is_heredoc ? "true" : "false");
		ft_printf("Delimiter: %s\n", cmd->delimiter ? cmd->delimiter : "(null)");
		ft_printf("Heredoc FD: %d\n", cmd->heredoc_fd);
		ft_printf("Heredoc Temp: %s\n", cmd->heredoc_temp ? cmd->heredoc_temp : "(null)");

		// Next command
		ft_printf("--------------------------\n");
		cmd = cmd->next;
		cmd_index++;
	}
}

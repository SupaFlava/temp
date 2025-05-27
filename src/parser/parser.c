/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmhazres <rmhazres@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/03 14:20:07 by rmhazres      #+#    #+#                 */
/*   Updated: 2025/05/28 00:34:19 by jbaetsen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	append_to_args(t_mshell *shell, t_command *command, char *content)
{
	int i;
	int j;
	char **new_args;

	i = 0;
	if (!command->args) // if theres no args added to command yet
	{
		command->args = ft_malloc_s(shell,(sizeof(char *) * 2), MEM_TEMP);	//mallocs for 2x a char *
		command->args[0] = ft_strdup_s(shell, content, MEM_TEMP);		//mallocs char * 1 for the actual needed space for the content
		command->args[1] = NULL;					//second needs 2 be null for execve()
		return (0);
	}
	while (command->args[i]) // go to the end of current args
		i++;
	new_args = ft_malloc_s(shell,(sizeof(char *) * (i + 2)), MEM_TEMP); //malloc for the current size + 2 (content + NULL)
	if (!new_args)
		return (1);
	j = 0;
	while (j < i)
	{
		new_args[j] = command->args[j];
		j++;
	}
	new_args[i] = ft_strdup_s(shell, content, MEM_TEMP);
	if (!new_args)
		return(1);
	new_args[i + 1] = NULL;
	//free (command->args);
	command->args = new_args;
	return (0);
}

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

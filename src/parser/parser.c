/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmhazres <rmhazres@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/03 14:20:07 by rmhazres      #+#    #+#                 */
/*   Updated: 2025/05/21 15:47:58 by jbaetsen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	append_to_args(t_command *command, char *content)
{
	int i;
	int j;
	char **new_args;

	i = 0;
	if (!command->args) // if theres no args added to command yet
	{
		command->args = malloc(sizeof(char *) * 2);	//mallocs for 2x a char *
		command->args[0] = ft_strdup(content);		//mallocs char * 1 for the actual needed space for the content
		command->args[1] = NULL;					//second needs 2 be null for execve()
		return ;
	}
	while (command->args[i]) // go to the end of current args
		i++;
	new_args = malloc(sizeof(char *) * (1 + 2)); //malloc for the current size + content + NULL
	if (!new_args)
		return ;
	j = 0;
	while (j < i)
	{
		new_args[j] = command->args[j];
		j++;
	}
	new_args[i] = ft_strdup(content);
	new_args[i + 1] = NULL;
	free (command->args);
	command->args = new_args;
}

int	parse_tokens_to_cmds(t_mshell *shell)
{
	t_token		*token;
	t_command *command;

	token = shell->tokens;
	command = create_command();
	while (token && token->type != TOK_PIPE)
	{
		if (token->type == TOK_WORD || token->type == TOK_ENV_VAR || token->type == TOK_EXIT_STATUS)
			append_to_args(command, token->content);
	}



	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmhazres <rmhazres@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/02 15:47:17 by jbaetsen      #+#    #+#                 */
/*   Updated: 2025/05/13 15:53:45 by jbaetsen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*create_command(void)
{
	t_command	*command;

	command = malloc(sizeof(t_command));
	if (!command)
		return (NULL);
	command->args = NULL;
	command->infile = NULL;
	command->outfile = NULL;
	command->append = 0;
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

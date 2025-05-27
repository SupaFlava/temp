/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmhazres <rmhazres@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/01 14:23:28 by jbaetsen      #+#    #+#                 */
/*   Updated: 2025/05/27 21:09:18 by jbaetsen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv/*, char **envp*/)
{
	t_mshell shell;
	(void)argc;
	(void)argv;

	if (shell_init(&shell) == EXIT_FAILURE)
		return(EXIT_FAILURE);
	setup_signals();
	//init_env(&shell ,envp);
	// t_command cmd = {
	// 	.args = (char *[]){"cd",NULL}
	// };

	while (1)
	{
		shell.line = read_input();
		if (shell.line && *shell.line)
		{
			add_history(shell.line);
			shell.tokens = lexer(&shell);
			if (!shell.tokens)
				ft_printf("ERROR\n");
			else
				print_tokens(shell.tokens);
		}
		// run_builtin(&cmd, &shell); // this is a tester
		free(shell.line);
		shell.line = NULL;
		ft_free(&shell, MEM_TEMP);
	}
	rl_clear_history();
	//clear_history(); // this for mac
	return (0);
}

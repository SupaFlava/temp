/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmhazres <rmhazres@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/01 14:23:28 by jbaetsen      #+#    #+#                 */
/*   Updated: 2025/06/05 15:45:06 by jbaetsen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_mshell	shell;

	(void)argc;
	(void)argv;

	shell_init(&shell);
    setup_signals();
	init_env(&shell ,envp);

	// t_command cmd2 = {
	// 	.args = (char *[]){"wc", NULL},
	// 	.infile = NULL,
	// 	.outfile = NULL,
	// 	.append = 0,
	// 	.next = NULL
	// };
	// (void)cmd2;
	// t_command cmd1 = {
	// 	.args = (char *[]){"cd", "/", NULL},
	// 	.infile = NULL,
	// 	.outfile = NULL,
	// 	.append = 0,
	// 	.next = NULL
	// };
	
	// (void) cmd1;
	// t_command cmd0 = {
	// 	.args = (char *[]){"/bin/ls", NULL},
	// 	.infile = NULL,
	// 	.outfile = NULL,
	// 	.append = 0,
	// 	.next = NULL
	// };

	//shell.commands = &cmd0;
	while (1)
	{
		shell.line = read_input();
		if (shell.line && *shell.line)
		{
			add_history(shell.line);
			shell.tokens = lexer(&shell);
			if (!shell.tokens)
				ft_printf("ERROR\n");
			// else
			// 	print_tokens(shell.tokens); // temp to see registered tokens
			shell.commands = parser(&shell);
			print_commands(shell.commands); // temp to see registered commands
		}
		if (shell.commands)
			execute_cmd(&shell);
		free(shell.line);
		shell.line = NULL;
		ft_free(&shell, MEM_TEMP);
	}
	rl_clear_history();
	//clear_history(); // this for mac
	return (0);
}

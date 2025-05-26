/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmhazres <rmhazres@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:23:28 by jbaetsen          #+#    #+#             */
/*   Updated: 2025/05/26 12:41:32 by rmhazres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_mshell shell;
	(void)argc;
	(void)argv;

	if (shell_init(&shell) == EXIT_FAILURE)
		return(EXIT_FAILURE);
    setup_signals();
	init_env(&shell ,envp);

	t_command cmd2 = {
		.args = (char *[]){"wc", NULL},
		.infile = NULL,
		.outfile = NULL,
		.append = 0,
		.next = NULL
	};
	
	t_command cmd1 = {
		.args = (char *[]){"echo", "hello", NULL},
		.infile = NULL,
		.outfile = NULL,
		.append = 0,
		.next = &cmd2
	};
	
	t_command cmd0 = {
		.args = (char *[]){"ls", NULL},
		.infile = NULL,
		.outfile = NULL,
		.append = 0,
		.next = &cmd1
	};
	shell.cmds = cmd0;
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
		execute_cmd(&shell);
	//	run_builtin(&cmd, &shell); // this is a tester
		free(shell.line);
		shell.line = NULL;
		ft_free(&shell, MEM_TEMP);
	}
	rl_clear_history();
	//clear_history(); // this for mac
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmhazres <rmhazres@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:23:28 by jbaetsen          #+#    #+#             */
/*   Updated: 2025/06/01 17:36:27 by rmhazres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_mshell shell;
	(void)argc;
	(void)argv;

	shell_init(&shell);
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
		.args = (char *[]){"cd", "/", NULL},
		.infile = NULL,
		.outfile = NULL,
		.append = 0,
		.next = NULL
	};
	
	t_command cmd0 = {
		.args = (char *[]){"echo","hi", NULL},
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmhazres <rmhazres@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/01 14:23:28 by jbaetsen      #+#    #+#                 */
/*   Updated: 2025/06/26 21:13:22 by jbaetsen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_mshell	shell;

	(void)argc;
	(void)argv;

	shell_init(&shell);
	init_env(&shell ,envp);
	while (1)
	{
		setup_signals();
		g_signal = 0;
		shell.line = read_input();
		if (shell.line && *shell.line)
		{
			add_history(shell.line);
			process_input(&shell);
			if(prep_heredoc(&shell) != 0)
				continue; // should clean up later
			if (shell.commands)
				shell.exit_status = execute_cmd(&shell);
		}
		if (g_signal == SIGINT)
		{
			shell.exit_status = 130;
			g_signal = 0;
			continue;
		}

		free(shell.line);
		shell.line = NULL;
		ft_free(&shell, MEM_TEMP);
	}
	rl_clear_history();
	//clear_history(); // this for mac
	return (0);
}

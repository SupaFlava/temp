/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmhazres <rmhazres@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/01 14:23:28 by jbaetsen      #+#    #+#                 */
/*   Updated: 2025/06/29 20:22:58 by jbaetsen      ########   odam.nl         */
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
		shell.line = read_input();
		check_global(&shell);
		if (shell.line && *shell.line)
		{
			add_history(shell.line);
			process_input(&shell);
			if(prep_heredoc(&shell) != 0)
				continue; // should clean up later
			if (shell.commands)
				shell.exit_status = execute_cmd(&shell);
		}
		free(shell.line);
		shell.line = NULL;
		ft_free(&shell, MEM_TEMP);
	}
	rl_clear_history();
	ft_free(&shell, MEM_LONG);
	//clear_history(); // this for mac
	return (0);
}

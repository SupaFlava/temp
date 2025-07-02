/* ************************************************************************** */
/*                                                                            */
<<<<<<< HEAD
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmhazres <rmhazres@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/01 14:23:28 by jbaetsen      #+#    #+#                 */
/*   Updated: 2025/07/02 13:29:56 by jbaetsen      ########   odam.nl         */
=======
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmhazres <rmhazres@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:23:28 by jbaetsen          #+#    #+#             */
/*   Updated: 2025/07/02 14:29:34 by rmhazres         ###   ########.fr       */
>>>>>>> origin/main
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_shell(t_mshell *shell)
{
	add_history(shell->line);
	process_input(shell);
	if (prep_heredoc(shell) != 0)
	{
		free(shell->line);
		shell->line = NULL;
		ft_free(shell, MEM_TEMP);
		return ;
	}
	if (shell->commands)
		shell->exit_status = execute_cmd(shell);
}

int	main(int argc, char **argv, char **envp)
{
	t_mshell	shell;

	(void)argc;
	(void)argv;
	shell_init(&shell);
<<<<<<< HEAD
	init_env(&shell, envp);
=======
	if (init_env(&shell, envp) == ERROR)
		return (ft_free(&shell, MEM_LONG), EXIT_FAILURE);
>>>>>>> origin/main
	while (1)
	{
		setup_signals();
		shell.line = read_input();
		check_global(&shell);
		if (shell.line && *shell.line)
<<<<<<< HEAD
		{
			add_history(shell.line);
			process_input(&shell);
			if (prep_heredoc(&shell) != 0)
				continue ; // should clean up later
			if (shell.commands)
				shell.exit_status = execute_cmd(&shell);
		}
		free(shell.line);
		shell.line = NULL;
=======
			run_shell(&shell);
>>>>>>> origin/main
		ft_free(&shell, MEM_TEMP);
	}
	rl_clear_history();
	ft_free(&shell, MEM_LONG);
	return (0);
}

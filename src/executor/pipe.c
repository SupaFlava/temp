/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipe.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmhazres <rmhazres@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/10 11:21:26 by rmhazres      #+#    #+#                 */
/*   Updated: 2025/07/02 14:49:41 by jbaetsen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	wait_for_pid(int amount, int pids[], t_mshell *shell)
{
	int	i;
	int	status;

	i = 0;
	status = -1;
	shell->exit_status = 0;
	while (i < amount)
	{
		waitpid(pids[i], &status, 0);
		if (i == amount - 1)
		{
			if (WIFSIGNALED(status))
			{
				g_signal = WTERMSIG(status);
				if (g_signal == SIGINT)
					write(1, "\n", 1);
				else if (g_signal == SIGQUIT)
					write(1, "Quit: 3\n", 8);
			}
			else if (WIFEXITED(status))
				shell->exit_status = WEXITSTATUS(status);
		}
		i++;
	}
}

static int	prep_pipe(t_command *cmd, int *fds)
{
	if (cmd->next)
	{
		if (pipe(fds) == -1)
		{
			ft_putstr_fd("error\n", STDERR_FILENO);
			return (-1);
		}
	}
	return (0);
}

static pid_t	run_child(t_command *cmd, t_exec_ctx *ctx, t_mshell *shell)
{
	pid_t	pid;

	if (!cmd || !cmd->args || !cmd->args[0])
		return (ft_putstr_fd("minishell: empty command\n", STDERR_FILENO), -1);
	pid = fork();
	if (pid == -1)
		return (perror("Fork"), -1);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (ctx->prev_fd != -1)
			dup2(ctx->prev_fd, STDIN_FILENO);
		if (cmd->next)
			dup2(ctx->fds[1], STDOUT_FILENO);
		close_fds(ctx->prev_fd, ctx->fds[0], ctx->fds[1]);
		if (handle_redir(cmd) < 0)
			exit(EXIT_FAILURE);
		if (is_builtin(cmd))
			exit(run_builtin(cmd, shell));
		else
			check_exec(cmd, shell);
		exit(0);
	}
	return (pid);
}

int	execute_pipeline(t_command *cmd, t_mshell *shell, t_exec_ctx *ctx)
{
	pid_t	pid;

	while (cmd)
	{
		if (prep_pipe(cmd, ctx->fds) < 0)
			return (1);
		if (ctx->child_count >= MAX_CHILDREN)
			return (print_err("minishell", NULL, "many child processes"), 1);
		pid = run_child(cmd, ctx, shell);
		if (pid < 0)
			return (1);
		ctx->child_pids[ctx->child_count++] = pid;
		if (cmd->is_heredoc && cmd->heredoc_fd != -1)
		{
			close(cmd->heredoc_fd);
			cmd->heredoc_fd = -1;
		}
		close_parent_fds(cmd, &ctx->prev_fd, ctx->fds);
		cmd = cmd->next;
	}
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	wait_for_pid(ctx->child_count, ctx->child_pids, shell);
	setup_signals();
	return (shell->exit_status);
}

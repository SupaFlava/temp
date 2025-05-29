/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tester.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmhazres <rmhazres@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/06 15:42:35 by rmhazres      #+#    #+#                 */
/*   Updated: 2025/05/29 21:30:46 by jbaetsen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"


int run_builtin(t_command *cmd, t_mshell *shell)
{
    if (ft_strncmp(cmd->args[0], "cd", ft_strlen(cmd->args[0])) == 0)
        return builtin_cd(shell, cmd->args);
    else if (ft_strncmp(cmd->args[0], "pwd", ft_strlen(cmd->args[0])) == 0)
        return builtin_pwd(shell);
	else if (ft_strncmp(cmd->args[0], "echo",ft_strlen(cmd->args[0])) == 0)
		return(builtin_echo(shell, cmd->args));
	else if (ft_strncmp(cmd->args[0], "env",ft_strlen(cmd->args[0])) == 0)
		return(builtin_env(shell, cmd->args));
	else
		return (0);
}

void	print_commands(t_mshell *shell)
{
	t_command	*cmd;
	int			i;
	int			cmd_num;


	cmd = shell->commands;
	if (!cmd)
	{
		printf("No commands registered.\n");
		return;
	}
	cmd_num = 1;
	while (cmd)
	{
		printf("Command %d:\n", cmd_num);

		// Arguments
		if (!cmd->args)
			printf("  Args: (none)\n");
		else
		{
			i = 0;
			while (cmd->args[i])
			{
				printf("  Arg[%d]: %s\n", i, cmd->args[i]);
				i++;
			}
		}

		// Input file
		if (cmd->infile)
			printf("  Infile: %s\n", cmd->infile);
		else
			printf("  Infile: (none)\n");

		// Output file
		if (cmd->outfile)
			printf("  Outfile: %s\n", cmd->outfile);
		else
			printf("  Outfile: (none)\n");

		// Append flag
		printf("  Append: %s\n", cmd->append ? "yes" : "no");

		// Builtin flag
		printf("  Is Builtin: %s\n", cmd->is_builtin ? "yes" : "no");

		cmd = cmd->next;
		cmd_num++;
	}
}

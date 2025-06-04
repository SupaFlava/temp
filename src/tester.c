/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tester.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmhazres <rmhazres@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/06 15:42:35 by rmhazres      #+#    #+#                 */
/*   Updated: 2025/06/04 22:38:52 by jbaetsen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"


int run_builtin(t_command *cmd, t_mshell *shell)
{
	if (!cmd)
		return (0);
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

void	print_commands(t_command *cmd)
{
	int	i;

	while (cmd)
	{
		printf("Command:\n");
		i = 0;
		if (cmd->args)
		{
			while (cmd->args[i])
			{
				printf("  arg[%d]: %s\n", i, cmd->args[i]);
				i++;
			}
		}
		else
			printf("  args: (null)\n");
		printf("  infile: %s\n", cmd->infile ? cmd->infile : "(null)");
		printf("  outfile: %s\n", cmd->outfile ? cmd->outfile : "(null)");
		printf("  append: %d\n", cmd->append);
		printf("  is_builtin: %d\n", cmd->is_builtin);
		printf("--------------------------\n");
		cmd = cmd->next;
	}
}

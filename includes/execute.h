/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmhazres <rmhazres@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 12:22:05 by rmhazres          #+#    #+#             */
/*   Updated: 2025/06/15 14:04:18 by rmhazres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "minishell.h"

int		execute_cmd(t_mshell *shell);
int		handle_redir(t_command *cmd);
int		check_exec(t_command *cmd, t_mshell *shell);
char	**env_to_envp(t_mshell *shell);
char	*find_in_path(char *arg, t_env *env_lst);
int		is_executable(const char *path);

// PIPE
int execute_pipeline(t_command *cmd, t_mshell *shell, t_exec_ctx *ctx);

//HEREDOC 
int     handle_heredoc(t_command *cmd,const char *filename ,t_mshell *shell);
int     fork_heredoc(t_command *cmd, t_mshell *shell,int index);
int     prep_heredoc(t_mshell *shell);

#endif
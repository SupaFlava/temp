/* ************************************************************************** */
/*                                                                            */
<<<<<<< HEAD
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmhazres <rmhazres@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 13:18:35 by jbaetsen          #+#    #+#             */
/*   Updated: 2025/05/06 15:53:58 by rmhazres         ###   ########.fr       */
=======
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmhazres <rmhazres@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/02 13:18:35 by jbaetsen      #+#    #+#                 */
/*   Updated: 2025/05/08 15:07:51 by jbaetsen      ########   odam.nl         */
>>>>>>> 98c9e99b789698c80b7911da8ff1b62d06c8fe28
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "signals.h"
# include "libft.h"
# include "parse.h"
# include "typedefs.h"
# include "env.h"
# include "utils.h"
<<<<<<< HEAD
# include "builtins.h"

int run_builtin(t_command *cmd, t_mshell *shell);

=======
# include "lexer.h"
>>>>>>> 98c9e99b789698c80b7911da8ff1b62d06c8fe28
#endif
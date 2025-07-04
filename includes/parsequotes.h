/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsequotes.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbaetsen <jbaetsen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/02 16:57:44 by jbaetsen      #+#    #+#                 */
/*   Updated: 2025/07/02 16:57:47 by jbaetsen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSEQUOTES_H
# define PARSEQUOTES_H

// includes
# include "typedefs.h"
# include "parsequotes.h"
# include "utils.h"

// parse_quotes.c
int	concat_last_arg(t_mshell *shell, t_command *cmd, t_parser *p, char *cont);
int	add_new_arg(t_mshell *shell, t_command *cmd, t_parser *p, char *content);
int	add_or_concat_arg(t_mshell *shell, t_parser *p);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmhazres <rmhazres@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 12:52:59 by jbaetsen          #+#    #+#             */
/*   Updated: 2025/07/02 14:33:14 by rmhazres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

// includes
# include "typedefs.h"
# include <signal.h>

extern volatile sig_atomic_t	g_signal;

//function prototypes
void	setup_signals(void);
void	sigint_heredoc(int sig);
void	handle_sigint(int sig);
void	check_global(t_mshell *shell);

#endif
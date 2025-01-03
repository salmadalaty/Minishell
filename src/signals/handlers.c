/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handelers.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ral-faya <ral-faya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 15:33:59 by ral-faya          #+#    #+#             */
/*   Updated: 2024/09/14 15:37:13 by ral-faya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"

static void	ft_signal(int signum, t_handler *handler);

void	wait_user_signals(void)
{
	ft_signal(SIGINT, show_new_prompt);
	ft_signal(SIGQUIT, SIG_IGN);
}

void	wait_child_signals(void)
{
	ft_signal(SIGINT, exit_child);
	ft_signal(SIGQUIT, exit_child);
}

void	wait_heredoc_signals(void)
{
	ft_signal(SIGINT, exit_heredoc);
	ft_signal(SIGQUIT, SIG_IGN);
}

void	heredoc_parent_sighandler(void)
{
	ft_signal(SIGINT, SIG_IGN);
	ft_signal(SIGQUIT, SIG_IGN);
}

static void	ft_signal(int signum, t_handler *handler)
{
	struct sigaction	action;

	action.sa_handler = handler;
	sigemptyset(&action.sa_mask);
	action.sa_flags = SA_RESTART;
	sigaction(signum, &action, NULL);
}

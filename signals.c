/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrancav & everolla <lfrancav@student.4    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 19:34:39 by lfrancav &        #+#    #+#             */
/*   Updated: 2024/02/20 22:21:36 by lfrancav &       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sig_prompt(int sig)
{
	g_signal = sig;
	if (sig == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

static void	sig_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		close(0);
	}
}

static void	sig_silent(int sig)
{
	g_signal = sig;
}

void	ft_set_signals(int mode)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (mode == PROMPT || mode == HEREDOC)
	{
		sa.sa_handler = &sig_prompt;
		if (mode == HEREDOC)
			sa.sa_handler = &sig_heredoc;
		sigaction(SIGINT, &sa, 0);
		sa.sa_handler = SIG_IGN;
		sigemptyset(&sa.sa_mask);
		sigaction(SIGQUIT, &sa, 0);
		return ;
	}
	else if (mode == FORK)
		sa.sa_handler = SIG_DFL;
	else if (mode == SILENT)
	{
		sa.sa_flags = SA_RESTART;
		sa.sa_handler = sig_silent;
	}
	sigaction(SIGQUIT, &sa, 0);
	sigaction(SIGINT, &sa, 0);
}

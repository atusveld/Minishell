/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jovieira <jovieira@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/20 14:40:22 by jovieira      #+#    #+#                 */
/*   Updated: 2024/08/19 13:50:42 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <termios.h>
// #include <asm-generic/termbits.h>


void	ignore_signal(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	child_ctrl_c(int sig)
{
	(void)sig;
	rl_redisplay();
	exit(1);
}

void	parent_ctrl_c(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	unset_signals(int sig)
{
	if (sig == 1)
	{
		signal(SIGINT, child_ctrl_c);
		signal(SIGQUIT, SIG_DFL);
	}
	else
	{
		signal(SIGINT, parent_ctrl_c);
		signal(SIGQUIT, SIG_IGN);
	}
}


void	set_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jovieira <jovieira@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/20 14:40:22 by jovieira      #+#    #+#                 */
/*   Updated: 2024/08/14 15:42:03 by jovieira      ########   odam.nl         */
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

void	signal_ctrl_c(int sig)
{
	(void)sig;
	// write(1, CTRL_C, ft_strlen(CTRL_C));
	// write(1, "\n", 1);
	// rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	// exit(1);
}

void	signal_ctrl_d(int sig)
{
	(void)sig;
	write(2, CTRL_D, ft_strlen(CTRL_D));
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	unset_signals(void)
{
	// signal(SIGINT, SIG_DFL);
	// signal(SIGTERM, SIG_DFL);
	signal(SIGINT, signal_ctrl_c);
	signal(SIGTERM, signal_ctrl_d);
	signal(SIGQUIT, SIG_DFL);
}


void	set_signals(void)
{
	signal(SIGINT, signal_ctrl_c);
	signal(SIGTERM, signal_ctrl_d);
	signal(SIGQUIT, SIG_IGN);
}

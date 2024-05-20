/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jovieira <jovieira@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/29 12:08:58 by jovieira      #+#    #+#                 */
/*   Updated: 2024/05/08 15:32:05 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/token.h"
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/stat.h>

int	here_err(pid_t PID)
{
	if (PID == -1)
	{
		write(STDERR_FILENO, "Fork failed.\n", 14);
		return (1);
	}
	return (0);
}


void	ign_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	unset_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	here_doc(t_token	*token)
{
	int	stat;
	pid_t	PID;
	t_data	mini_data;
	(void)token;
	PID = fork();
	ign_signals();
	while (1)
	{
		if (PID == 0)
		{
			ign_signals();
			mini_data.input = readline("> ");
		}
		waitpid(PID, &stat, 0);
		printf("%s", mini_data.input);
	}
}

void	found_here(t_token	*token)
{
	token->fd = 0;
	token->fd = open("tmp_here", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	here_doc(token);
	close(token->fd);
	exit(0);
}

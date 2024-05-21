/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jovieira <jovieira@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/29 12:08:58 by jovieira      #+#    #+#                 */
/*   Updated: 2024/05/21 16:59:08 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/parse.h"
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/stat.h>

int	here_err(pid_t PID)
{
	if (PID < 0)
	{
		write(STDERR_FILENO, "Fork failed.\n", 14);
		return (1);
	}
	return (0);
}


char	*remove_quote(char *delimiter)
{
	int i;

	i = 0;
	while (delimiter[i])
	{
		if ((delimiter[i] == '\'' || delimiter[i] == '"') && \
			(delimiter[ft_strlen(delimiter) - 1] == '\'' || delimiter[ft_strlen(delimiter) - 1] == '"'))
		{
			delimiter += 1;
			delimiter[ft_strlen(delimiter) - 1] = '\0';
		}
		i++;
	}
	return (delimiter);
}

void	write_line(char *delimiter, int fd, bool quotes)
{
	char *line;
	char *temp;

	temp = NULL;
	line = readline("> ");
	while (line)
	{
		if (!ft_strncmp(delimiter, line, ft_strlen(delimiter)))
			break;
		if (quotes == true)
		{
			while (ft_strchr(line, '$'))
			{
				// temp = line;
				printf("hello quote\n");
				break ;
				// line = expandable();// ainda por criar
				// free(temp);
			}
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		line = readline("> ");
	}
	free(line);
}


void	heredoc(char *delimiter, int fd)
{
	bool	quotes;

	quotes = false;
	if (ft_strchr(delimiter, '\'') || ft_strchr(delimiter, '"'))
	{
		delimiter = remove_quote(delimiter);
		quotes = true;
	}
	write_line(delimiter, fd, quotes);
}

void	init_doc(char *delimiter)
{
	int	fd;

	fd = open("tmp_here", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
	{
		// dar erro, escrever funct
		return ;
	}
	heredoc(delimiter, fd);
	// ft_add_redir(&data->redir_in, fd);
	// unlink("tmp_here");
	close(fd);
	_exit(0);
}

void	found_here(t_parse *data, char *delimiter)
{
	int		status;
	pid_t	pid;
	t_red	*here;

	here = ft_redir_new("tmp_here", HEREDOC);
	ft_add_redir(&data->redir_in, here);
	pid = fork();
	ignore_signal();
	if (here_err(pid))
		return ;
	if (pid == 0)
	{
		unset_signals();
		init_doc(delimiter);
	}
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
	{
		// clean if not
		return ;
	}
	set_signals();
	// data = data->next;
}
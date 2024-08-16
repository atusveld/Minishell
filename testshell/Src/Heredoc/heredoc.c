/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jovieira <jovieira@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/29 12:08:58 by jovieira      #+#    #+#                 */
/*   Updated: 2024/08/15 13:25:21 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/main.h"
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

char	*remove_quote(char *delimiter, char quote)
{
	int i;
	int	j;

	i = 0;
	while (delimiter[i])
	{
		if (delimiter[i] == quote)
		{
			j = skip_quotes(delimiter, i);
			if (delimiter[j] == '\0')
				return (delimiter);
			ft_memmove (delimiter + i, delimiter + i + 1, ft_strlen(delimiter + i));
			ft_memmove (delimiter + j - 1, delimiter + j, ft_strlen(delimiter + j - 1));
			i = j - 1;
		}
		else
			i++;
	}
	return (delimiter);
}

char	*remove_quote_unsp(char *delimiter)
{
	int i;
	int	j;

	i = 0;
	while (delimiter[i])
	{
		if (delimiter[i] == '\'' || delimiter[i] == '"')
		{
			j = skip_quotes(delimiter, i);
			if (delimiter[j] == '\0')
				return (delimiter);
			ft_memmove (delimiter + i, delimiter + i + 1, ft_strlen(delimiter + i));
			ft_memmove(delimiter + j - 1, delimiter + j, ft_strlen(delimiter + j - 1));
			i = j - 1;
		}
		else
			i++;
	}
	return (delimiter);
}

void	write_line(char *delimiter, int fd, bool quotes, t_main *main)
{
	char *line;

	line = readline("> ");
	while (line)
	{
		if (!ft_strncmp(delimiter, line, ft_strlen(delimiter)))
			break;
		if (quotes == false)
		{
			while (ft_strchr(line, '$'))
				line = expandable(line, main);
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		line = readline("> ");
	}
	if (!line)
		printf("%s%s')\n", CTRL_D, delimiter);
	free(line);
}


void	heredoc(char *delimiter, int fd, t_main *main)
{
	bool	quotes;

	quotes = false;
	if (ft_strchr(delimiter, '\'') || ft_strchr(delimiter, '"'))
	{	
		delimiter = remove_quote_unsp(delimiter);
		quotes = true;
	}
	write_line(delimiter, fd, quotes, main);
}

static void	init_doc(char *delimiter, t_main *main)
{
	int	fd;

	fd = open("tmp_here", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
	{
		// dar erro, escrever funct
		return ;
	}
	heredoc(delimiter, fd, main);
	close(fd);
	_exit(0);
}

int	found_here(t_main *main, t_parse *parse_temp, char *delimiter)
{
	int		status;
	pid_t	pid;
	t_red	*here;

	here = ft_redir_new("tmp_here", HEREDOC);
	if (!here)
		return (1);
	ft_add_redir(&parse_temp->redir_in, here);
	// free(here);
	pid = fork();
	ignore_signal();
	if (here_err(pid))
		return (1);
	if (pid == 0)
	{
		unset_signals(1);
		init_doc(delimiter, main);
		exit(0);
	}
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
	{
		// add cleaning if fail
		return (1);
	}
	unset_signals(0);
	return (1);
}

// t_token	*tmp;

// tmp = NULL;
// if (token == NULL)
// 	return ;
// tmp = token;
// while (token)
// {
// 	tmp = token;
// 	free(tmp->cont);
// 	token = token->next;
// 	free(tmp);
// }
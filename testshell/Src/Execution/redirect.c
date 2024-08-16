/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect.c                      	                    :+:    :+:        */
/*                                                     +:+                    */
/*   By: atusveld <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/03 15:26:55 by atusveld      #+#    #+#                 */
/*   Updated: 2022/09/07 17:40:34 by atusveld      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/shell.h"

void	ft_red_out(t_shell *shell)
{
	int	fd;
	
	if (!shell->parsed || !shell->parsed->redir_out)
        ft_error("parsing error, red_out", shell, 1);
	while (shell->parsed->redir_out)
	{
		if (shell->parsed->redir_out->type == APPEND)
			ft_append(shell);
		if (shell->parsed->redir_out->next)
		{
			fd = ft_create_file(shell);
			if (fd == -1)
				ft_error("invalid fd, red_out", shell, 1);
			ft_write_to_file(fd, shell);
			if (close(fd) == -1)
				ft_error("error closing fd, red_out", shell, 1);
		}
		shell->parsed->redir_out = shell->parsed->redir_out->next;
	}
}

void	ft_red_in(t_shell *shell)
{
	char	*filename;
	int		fd;

	if (!shell->parsed || !shell->parsed->redir_in)
        ft_error("parsing error, red_in", shell, 1);
	filename = shell->parsed->redir_in->filename;
	if (!filename)
		ft_error("invalid filename, red_in", shell, 1);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		ft_error("invalid fd, red_in", shell, 1);
	if (close(fd) == -1)
		ft_error("error closing fd, red_in", shell, 1);
}

int	ft_create_file(t_shell *shell)
{
	char	*filename;
	int		fd;

	if (!shell->parsed || !shell->parsed->redir_out)
        ft_error("parsing error, create_file", shell, 1);
	filename = shell->parsed->redir_out->filename;
	if (!filename)
		ft_error("invalid filename, create file", shell, 1);
	fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0666);
	if (fd == -1)
		ft_error("invlid fd, create file", shell, 1);
	return (fd);
}

void	ft_write_to_file(int fd, t_shell *shell)
{
	char	*text;
	int		i;

	i = 0;
	text = shell->parsed->argv[1];
	if (fd == -1)
		ft_error("fd, write to file", shell, 1);
	while (text[i])
	{
		write(fd, &text[i], 1);
		i++;
	}
	if (write(fd, "\n", 1) == -1)
		ft_error("write, write to file", shell, 1);
	if (close(fd) == -1)
		ft_error("close, write to file", shell, 1);
}

void	ft_append(t_shell *shell)
{
	char	*filename;
	int 	fd;
	
	filename = shell->parsed->redir_out->filename;
	fd = open(filename, O_CREAT | O_RDWR | O_APPEND, 0666);
	if (fd == -1)
		ft_error("invalid fd, append file", shell, 1);
	ft_write_to_file(fd, shell);
	if (close(fd) == -1)
		ft_error("error closing fd, append file", shell, 1);
}

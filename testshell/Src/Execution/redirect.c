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

#include "../../Includes/main.h"

void	ft_red_out(t_parse *parsed)
{
	int	fd;
	
	if (!parsed || !parsed->redir_out)
        ft_error("red_out, parsed", 1);
	while (parsed->redir_out)
	{
		if (parsed->redir_out->type == APPEND)
			ft_append(parsed);
		if (parsed->redir_out->next)
		{
			fd = ft_create_file(parsed);
			if (fd == -1)
				ft_error("fd, create file", 1);
			ft_write_to_file(fd, parsed);
			if (close(fd) == -1)
				ft_error("close, create file", 1);
		}
		parsed->redir_out = parsed->redir_out->next;
	}
}
void	ft_red_in(t_parse *parsed)
{
	char	*filename;
	int		fd;

	if (!parsed || !parsed->redir_in)
        ft_error("red_in, parsed", 1);
	filename = parsed->redir_in->filename;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		ft_error("red_in, fd", 1);
	if (close(fd) == -1)
		ft_error("red_in, close", 1);
}

int	ft_create_file(t_parse *parsed)
{
	char	*filename;
	int		fd;

	if (!parsed || !parsed->redir_out)
        ft_error("create_file, parsed", 1);
	filename = parsed->redir_out->filename;
	if (!filename)
		ft_error("filename, create file", 1);
	fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0666);
	if (fd == -1)
		ft_error("fd, create file", 1);
	return (fd);
}

void	ft_write_to_file(int fd, t_parse *parsed)
{
	char	*text;
	int		i;

	i = 0;
	text = parsed->argv[1];
	if (fd == -1)
		ft_error("fd, write to file", 1);
	while (text[i])
	{
		write(fd, &text[i], 1);
		i++;
	}
	if (write(fd, "\n", 1) == -1)
		ft_error("write, write to file", 1);
	if (close(fd) == -1)
		ft_error("close, write to file", 1);
}

void	ft_append(t_parse *parsed)
{
	char	*filename;
	int 	fd;
	
	filename = parsed->redir_out->filename;
	fd = open(filename, O_CREAT | O_RDWR | O_APPEND, 0666);
	if (fd == -1)
		ft_error("fd, append file", 1);
	ft_write_to_file(fd, parsed);
	if (close(fd) == -1)
		ft_error("close, append file", 1);
}

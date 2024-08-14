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
        return;
	if (parsed->redir_out->type == APPEND)
		ft_append(parsed);
	if (parsed->redir_out->next)
	{
		while (parsed->redir_out)
		{
			fd = ft_create_file(parsed);
			if (fd == -1)
			{
				ft_error("fd, create file", 1);
				return ;
			}
			parsed->redir_out = parsed->redir_out->next;
		}
		ft_write_to_file(fd, parsed);
	}
	else
	{
		fd = ft_create_file(parsed);
		if (fd == -1)
		{
			ft_error("fd, append file", 1);
			return ;
		}
		ft_write_to_file(fd, parsed);
	}
}
void	ft_red_in(t_parse *parsed)
{
	char	*filename;
	int		fd;

	if (!parsed || !parsed->redir_in)
        return;
	filename = parsed->redir_in->filename;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		ft_error("red_in, fd", 1);
		return ;
	}
	// if (dup2(fd, STDIN_FILENO) < 0)
	// {
	// 	close(fd);
	// 	return ;
	// }
	if (close(fd))
		return ;
}

int	ft_create_file(t_parse *parsed)
{
	char	*filename;
	int		fd;

	if (!parsed || !parsed->redir_out)
        return (-1);
	filename = parsed->redir_out->filename;
	fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0666);
	return (fd);
}

void	ft_write_to_file(int fd, t_parse *parsed)
{
	char	*text;
	int		i;

	i = 0;
	text = parsed->argv[1];
	if (text == NULL)
		return ;
	if (fd == -1)
		ft_error("fd, write to file", 1);
	while (text[i])
	{
		write(fd, &text[i], 1);
		i++;
	}
	write(fd, "\n", 1);
	close(fd);
}

void	ft_append(t_parse *parsed)
{
	char	*filename;
	int 	fd;
	
	filename = parsed->redir_out->filename;
	fd = open(filename, O_CREAT | O_RDWR | O_APPEND, 0666);
	printf("fd = %i file %s\n", fd, filename);
	ft_write_to_file(fd, parsed);
}

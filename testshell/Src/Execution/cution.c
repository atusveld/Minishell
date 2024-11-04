/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cution.c                      	                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: atusveld <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/03 15:26:55 by atusveld      #+#    #+#                 */
/*   Updated: 2022/09/07 17:40:34 by atusveld      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/shell.h"

int	ft_red_single(t_shell *shell)
{
	char	*filename;
	int 	fd;

	printf("=[REDSINGLE]=\n");
	if (!shell->parsed || !shell->parsed->redir_out)
        ft_error("parsing error, red_single", shell, 1);
	filename = shell->parsed->redir_out->filename;
	if (!filename)
		ft_error("invalid filename, red_single", shell, 1);
	fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0666);
	if (fd < 0)
		return (ft_error("invalid fd, red_single", shell, 1), -1);
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		if (close(fd) == -1)
			ft_error("error closing fd, red_single", shell, 1);
		return (ft_error("dup2 failed, red_single", shell, 1), -1);
	}
	return (fd);
}

int	ft_count_cmd(t_parse *parsed)
{
	t_parse	*tmp;
	int		i;

	i = 0;
	tmp = parsed;
	while (tmp != NULL)
	{
		tmp = tmp->next;
		i++;
	}
	free(tmp);
	return (i);
}

t_pipe	*ft_init_pipes(t_shell *shell, int cmd_count)
{
    t_pipe	*pipes;
    int		i;

    pipes = malloc(sizeof(t_pipe) * (cmd_count - 1));
    if (!pipes)
        return (NULL);
    i = 0;
    while (i < cmd_count - 1)
    {
        if (pipe(pipes[i].tube) == -1)
        {
			free(pipes);
			pipes = NULL;
			ft_error("pipe failed", shell, 1);
		}
        i++;
    }
    return (pipes);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                      	                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: atusveld <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/03 15:26:55 by atusveld      #+#    #+#                 */
/*   Updated: 2022/09/07 17:40:34 by atusveld      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/main.h"

int	ft_fork(void)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		return (-1);
	return (pid);
}
void	ft_dup_exe(t_main *main, t_pipe *pipes, int i, int cmd_c)
{
    char	*path;
    char	**env_arr;

    env_arr = ft_env_to_array(main->env);
    path = get_cmd_path(main);
    if (i == 1)
    {
        close(pipes[i - 1].tube[0]);
        dup2(pipes[i - 1].tube[1], STDOUT_FILENO);
    }
    else if (i == cmd_c)
    {
        close(pipes[i - 2].tube[1]);
        dup2(pipes[i - 2].tube[0], STDIN_FILENO);
    }
    else
    {
        close(pipes[i - 2].tube[1]);
        dup2(pipes[i - 2].tube[0], STDIN_FILENO);
        close(pipes[i - 1].tube[0]);
        dup2(pipes[i - 1].tube[1], STDOUT_FILENO);
    }
    if ((execve(path, main->gen->cmd_args, env_arr)) < 0)
    {
        ft_free_arr(env_arr);
		if (errno == EACCES)
			exit(126);
		else
			exit(127);
    }
    ft_free_arr(env_arr);
}


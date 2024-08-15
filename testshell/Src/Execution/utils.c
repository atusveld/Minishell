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
		ft_error("Fork failed", 1);
	return (pid);
}

void ft_dup_exe(t_main *main, t_pipe *pipes, int i, int cmd_c)
{
    char *path;
    char **env_arr;

    env_arr = ft_env_to_array(main->env);
	if (!env_arr)
	{
		ft_free_arr(env_arr);
		ft_error("Error env to array, dup_exe", 1);
	}
    path = get_cmd_path(main);
	if (!path)
	{
		free(path);
		ft_error("Error getting path, dup_exe", 1);
	}
    ft_dup_pipes(pipes, i, cmd_c);
    ft_exec_cmd(main, path, env_arr);
	ft_free_arr(env_arr);
}

void ft_dup_pipes(t_pipe *pipes, int i, int cmd_c)
{
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
}

void ft_exec_cmd(t_main *main, char *path, char **env_arr)
{
    if ((execve(path, main->gen->cmd_args, env_arr)) < 0)
    {
        ft_free_arr(env_arr);
        if (errno == EACCES)
            ft_error("Permission denied", 126);
        else
            ft_error("Command not found", 127);
    }
    ft_free_arr(env_arr);
}

void	close_pipes(t_pipe *pipes, int cmd_c, int i)
{
	int	j;

	j = 0;
	while (j < cmd_c - 1)
	{
		if (j != i - 1)
			close(pipes[j].tube[1]);
		if (j != i - 2)
			close(pipes[j].tube[0]);
		j++;
	}
}


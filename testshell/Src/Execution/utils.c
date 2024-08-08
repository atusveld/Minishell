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
void	ft_fml(t_main *main, t_pipe *pipe, int i, int cmd_c)
{
	if (i == 1)
		ft_exe_first(main, pipe);
	else if (i != 1 && i != cmd_c)
		ft_exe_mid(main, pipe);
	else if (cmd_c == i)
		ft_exe_last(main, pipe);
}
void	ft_exe_first(t_main *main, t_pipe *pipe)
{
	char	*path;
	char	**env_arr;

	env_arr = ft_env_to_array(main->env);
	path = get_cmd_path(main);
	close(pipe->tube[0]);
	dup2(pipe->tube[1], STDOUT_FILENO);
	if ((execve(path, main->gen->cmd_args, env_arr)) < 0)
		ft_error("multi cmd1", main);
	ft_free_arr(env_arr);
}

void	ft_exe_mid(t_main *main, t_pipe *pipe)
{
	char	*path;
	char	**env_arr;

	env_arr = ft_env_to_array(main->env);
	path = get_cmd_path(main);
	close(pipe->tube[0]);
	dup2(pipe->tube[1], STDOUT_FILENO);
	dup2(pipe->in_fd, STDIN_FILENO);
	if ((execve(path, main->gen->cmd_args, env_arr)) < 0)
		ft_error("multi cmd2", main);
	ft_free_arr(env_arr);
}

void	ft_exe_last(t_main *main, t_pipe *pipe)
{
	char	*path;
	char	**env_arr;

	env_arr = ft_env_to_array(main->env);
	path = get_cmd_path(main);
	close(pipe->tube[1]);
	dup2(pipe->tube[0], STDIN_FILENO);
	dup2(pipe->in_fd, STDIN_FILENO);
	if ((execve(path, main->gen->cmd_args, env_arr)) < 0)
		ft_error("multi cmd3", main);
	ft_free_arr(env_arr);
}

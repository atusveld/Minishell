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

#include "../../Includes/alex.h"

int	ft_fork(void)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		ft_error("pid");
	return (pid);
}
void	ft_fml(t_gen *gen, t_pipe *pipe, int i, int cmd_c)
{
	if (i == 1)
		ft_exe_first(gen, pipe);
	else if (i != 1 && i != cmd_c)
		ft_exe_mid(gen, pipe);
	else if (cmd_c == i)
		ft_exe_last(gen, pipe);
}
void	ft_exe_first(t_gen *gen, t_pipe *pipe)
{
	char	*path;
	char	**env_arr;

	env_arr = ft_env_to_array(gen->env);
	path = get_cmd_path(gen);
	close(pipe->tube[0]);
	dup2(pipe->tube[1], STDOUT_FILENO);
	if ((execve(path, gen->cmd_args, env_arr)) < 0)
		ft_error("multi cmd1");
	ft_free_arr(env_arr);
}

void	ft_exe_mid(t_gen *gen, t_pipe *pipe)
{
	char	*path;
	char	**env_arr;

	env_arr = ft_env_to_array(gen->env);
	path = get_cmd_path(gen);
	close(pipe->tube[0]);
	dup2(pipe->tube[1], STDOUT_FILENO);
	dup2(pipe->in_fd, STDIN_FILENO);
	if ((execve(path, gen->cmd_args, env_arr)) < 0)
		ft_error("multi cmd2");
	ft_free_arr(env_arr);
}

void	ft_exe_last(t_gen *gen, t_pipe *pipe)
{
	char	*path;
	char	**env_arr;

	env_arr = ft_env_to_array(gen->env);
	path = get_cmd_path(gen);
	close(pipe->tube[1]);
	dup2(pipe->tube[0], STDIN_FILENO);
	dup2(pipe->in_fd, STDIN_FILENO);
	if ((execve(path, gen->cmd_args, env_arr)) < 0)
		ft_error("multi cmd3");
	ft_free_arr(env_arr);
}

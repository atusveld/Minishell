/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exe.c           	                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: atusveld <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/03 15:26:55 by atusveld      #+#    #+#                 */
/*   Updated: 2022/09/07 17:40:34 by atusveld      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/alex.h"

void	ft_exe(t_parse *parsed, t_gen *gen)
{	
	gen->cmd_args = parsed->argv;
	gen->env_paths = get_paths(gen);
	gen->cmd_path = get_cmd_path(gen);
	if (!parsed->next)
		ft_exe_single(gen, gen->env);
	else if (ft_if_builtin(gen, parsed) == 0)
		return ;
	else
		ft_exe_multi(gen, parsed);
}

int	ft_exe_single(t_gen *gen, t_env *env)
{
	int		status;
	pid_t	f_id;
	char	*path;

	f_id = fork();
	status = -1;
	path = get_cmd_path(gen);
	if (f_id < 0)
		ft_error("fork");
	else if (f_id == 0)
	{
		if ((execve(path, gen->cmd_args, ft_env_to_arr(env))) < 0)
			ft_error("child");
	}
	else
	{
		while (!WIFEXITED(status) && !WIFSIGNALED(status))
			waitpid(f_id, &status, WUNTRACED);
	}
	return (-1);
}

int	ft_exe_multi(t_gen *gen, t_parse *parsed)
{
	int		fd[2];
	char	*path;
	pid_t	pid;

	pid = fork();
	path = get_cmd_path(gen);
	if (pipe(fd) < 0)
		ft_error("pipe fail");
	if (pid < 0)
		ft_error("fork fail");
	if (pid == 0)
	{
		close(fd[0]);
		execve(path, gen->cmd_args, ft_env_to_arr(gen->env));
		parsed = parsed->next;
	}
	else
	{
		path = get_cmd_path(gen);
		execve(path, gen->cmd_args, ft_env_to_arr(gen->env));
	}
	dup2(fd[1], 1);
	return (-1);
}

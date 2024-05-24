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
	// char	**n_envp;
	gen->cmd_args = parsed->argv;
	gen->env_paths = get_paths(gen);
	gen->cmd_path = get_cmd_path(gen);
	if (ft_if_builtin(gen, parsed) == 0)// we're not going inside the buildt in funct YES WE ARE FODES
		return ;
	else if (!parsed->next)
		ft_exe_single(gen, gen->env);
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
	if (f_id == 0)
	{
		if ((execve(path, gen->cmd_args, ft_env_to_array(env))) < 0)
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
	t_cpro	*cpro;
	int		status;
	int		cmd_c;
	int		i;

	i = 0;
	status = -1;
	cmd_c = ft_count_cmd(parsed);
	while (cmd_c > i)
	{
		if (i == 0)
			cpro = ft_exe_first(gen);
		else if (i != 0 && i != cmd_c - 1)
			ft_exe_mid(gen);
		else
			ft_exe_last(gen, cpro);
		i++;
		parsed = parsed->next;
		gen->cmd_args = parsed->argv;
	}
	return (-1);
}

t_cpro	*ft_exe_first(t_gen *gen)
{
	char	*path;
	pid_t	pid;
	int		status;
	t_cpro	*cpro;

	cpro = ft_init_cpro();
	pid = cpro->pid;
	status = -1;
	path = get_cmd_path(gen);
	if (pipe(cpro->pipe) < 0)
		ft_error("pipe1");
	if 	(pid < 0)
		ft_error("fork1");
	if (pid == 0)
		{
			close(cpro->pipe[0]);
			dup2(cpro->pipe[1], STDOUT_FILENO);
			if ((execve(path, gen->cmd_args, ft_env_to_array(gen->env))) < 0)
				ft_error("child1");
		}
	else
	{
		while (!WIFEXITED(status) && !WIFSIGNALED(status))
			waitpid	(pid, &status, WUNTRACED);
	}
	return (cpro);
}
int	ft_exe_mid(t_gen *gen)
{
	char	*path;
	pid_t	pid;
	int		status;
	t_cpro	*cpro;

	cpro = ft_init_cpro();
	pid = cpro->pid;
	status = -1;
	path = get_cmd_path(gen);
	if (pipe(cpro->pipe) < 0)
		ft_error("pipe2");
	if 	(pid < 0)
		ft_error("fork2");
	if (pid == 0)
		{
			close(cpro->pipe[1]);
			dup2(cpro->pipe[0], STDIN_FILENO);
			if ((execve(path, gen->cmd_args, ft_env_to_array(gen->env))) < 0)
				ft_error("child2");
		}
	else
	{
		while (!WIFEXITED(status) && !WIFSIGNALED(status))
			waitpid	(pid, &status, WUNTRACED);
	}
	ft_free_cpro(cpro);
	return (-1);
}

int	ft_exe_last(t_gen *gen, t_cpro *cpro)
{
	char	*path;
	pid_t	pid;
	int		status;

	status = -1;
	pid = cpro->pid;
	path = get_cmd_path(gen);
	if (pipe(cpro->pipe) < 0)
		ft_error("pipe3");
	if 	(pid < 0)
		ft_error("fork3");
	if (pid == 0)
		{
			close(cpro->pipe[1]);
			dup2(cpro->pipe[0], cpro->in_fd);
			if ((execve(path, gen->cmd_args, ft_env_to_array(gen->env))) < 0)
				ft_error("child3");
		}
	else
	{
		while (!WIFEXITED(status) && !WIFSIGNALED(status))
			waitpid	(pid, &status, WUNTRACED);
	}
	ft_free_cpro(cpro);
	return (-1);
}

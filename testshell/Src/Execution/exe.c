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
	if (ft_if_builtin(gen, parsed) == 0)
		return ;
	if (!parsed->next)
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
	t_pipe	*pipe;
	int		status;
	int		cmd_c;
	int		pid;
	int		i;

	status = -1;
	i = 1;
	cmd_c = ft_count_cmd(parsed);
	pipe = ft_init_pipes();
	while (cmd_c >= i)
	{
		pid = fork();
		if (pid < 0)
			ft_error("pid");
		if (pid == 0)
		{
			if (i == 1)
				ft_exe_first(gen, pipe);
			else if (i != 1 && i != cmd_c)
				ft_exe_mid(gen, pipe);
			else if (cmd_c == i)
				ft_exe_last(gen, pipe);
		}
		else
		{
			close(pipe->tube[1]);
			if (waitpid(pid, &status, WUNTRACED) == - 1)
				ft_error("waitpid");
		}
		if (parsed->next)
		{
			pipe->in_fd = pipe->tube[0];
			parsed = parsed->next;
		}
		gen->cmd_args = parsed->argv;
		i++;
	}
	return (-1);
}

int	ft_exe_first(t_gen *gen, t_pipe *pipe)        //  FIRST COMMAND
{
	char	*path;
	char	**env_arr;

	
		dprintf(2, "==[FIRST CMD]==\n");
	env_arr = ft_env_to_array(gen->env);
	path = get_cmd_path(gen);
	close(pipe->tube[0]);
	dup2(pipe->tube[1], STDOUT_FILENO);
	if ((execve(path, gen->cmd_args, env_arr)) < 0)
		ft_error("child1");
	free(env_arr);
	return (-1);
}

int	ft_exe_mid(t_gen *gen, t_pipe *pipe)
{
	char	*path;
	char	**env_arr;

	
	dprintf(2, "==[MID CMD]==\n");
	env_arr = ft_env_to_array(gen->env);
	path = get_cmd_path(gen);
	close(pipe->tube[0]);
	dup2(pipe->tube[1], STDOUT_FILENO);
	dup2(pipe->in_fd, STDIN_FILENO);
	if ((execve(path, gen->cmd_args, env_arr)) < 0)
		ft_error("child2");
	free(env_arr);
	return (-1);
}

int	ft_exe_last(t_gen *gen, t_pipe *pipe)		// LAST COMMAND
{
	char	*path;
	char	**env_arr;

	dprintf(2, "==[LAST CMD]==\n");
	env_arr = ft_env_to_array(gen->env);
	path = get_cmd_path(gen);
	close(pipe->tube[1]);
	dup2(pipe->tube[0], STDIN_FILENO);
	dup2(pipe->in_fd, STDIN_FILENO);
	if ((execve(path, gen->cmd_args, env_arr)) < 0)
		ft_error("child3");
	free(env_arr);
	return (-1);
}

// int	ft_wait(int cmd_c)
// {
// 	int	i;
// 	int	status;

// 	status = -1;
// 	dprintf(2, "==[ENTER WAIT]==\n");
// 	i = 0;
// 	while (i < cmd_c - 1)
// 	{
// 		if (waitpid(pid[i], &status, WUNTRACED) == - 1)
// 			ft_error("waitpid");
// 		if (!WIFEXITED(status) && !WIFSIGNALED(status))
// 			ft_error("waitrr");
// 		i++;
// 		dprintf(2, "==[WAITIN']==\n");
// 	}
// 	dprintf(2, "==[EXIT WAIT]==\n");
// 	return (0);
// }

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
	int		status;
	pid_t	pid[2];
	char	*path;
	int		cmd_c;
	int		fd[2];
	int		i;

	i = 0;
	cmd_c = ft_count_cmd(parsed);
	status = -1;
	while (cmd_c > i)
	{
		pid[i] = fork();
		if (pipe(fd) < 0)
			ft_error("pipe");
		if (pid[i] < 0)
			ft_error("fork");
		gen->cmd_args = parsed->argv;
		path = get_cmd_path(gen);
		if (pid[i] == 0)
		{
			if (i == 0)
			{
				close(fd[0]);
				dup2(fd[1], STDOUT_FILENO);
				dprintf(2, "==[HERE1]==\n");
				if ((execve(path, gen->cmd_args, ft_env_to_array(gen->env))) < 0)
					ft_error("child");
			}
			else if (i != 0 && i != cmd_c - 1)
			{
				close(fd[1]);
				dup2(fd[0], STDOUT_FILENO);
				dprintf(2, "==[HERE2]==\n");
				if ((execve(path, gen->cmd_args, ft_env_to_array(gen->env))) < 0)
					ft_error("child");
			}
			else
			{
				close(fd[1]);
				dup2(fd[0], STDIN_FILENO);
				dprintf(2, "==[HERE3]==\n");
				if ((execve(path, gen->cmd_args, ft_env_to_array(gen->env))) < 0)
					ft_error("child");
			}
		}
		i++;
		parsed = parsed->next;
		dprintf(2, "==[HERE4]==\n");
	}
	i = 0;
	while (cmd_c > i)
	{
		dprintf(2, "==[HERE5]==\n");
		if (waitpid(pid[i], &status, WUNTRACED) == - 1)
			ft_error("pid");
		// if (!WIFEXITED(status) && !WIFSIGNALED(status))
		i++;
	}
	return (-1);
}

// void	ft_exe_mid_cmd(t_gen *gen, t_parse *parsed)
// {
// 	int		status;

// 	status = -1;
// 	if ((execve(gen->cmd_path, gen->cmd_args, ft_env_to_array(gen->env))) < 0)
// 		ft_error("child");
// }

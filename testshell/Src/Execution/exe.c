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
	if (ft_if_builtin(gen, parsed) == 0)// we're not going inside the buildt in funct yes we are
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
	pid_t	pid;
	char	*path;
	int		cmd_c;
	int		fd[2];
	int		i;

	i = 0;
	cmd_c = ft_count_cmd(parsed);
	printf("[CMDC =%d]\n", cmd_c);
	status = -1;
	while (cmd_c >= i)
	{
		gen->cmd_args = parsed->argv;
		path = get_cmd_path(gen);
		if (pipe(fd) < 0)
			ft_error("pipe");
		pid = fork();
		if (pid < 0)
			ft_error("fork");
		if (pid == 0)
		{
			if (i == 0)
			{
				close(fd[0]);
				dup2(fd[1], STDIN_FILENO);
				ft_exe_single(gen, gen->env);
				printf("==[HERE1]==\n");
			}
			else if (i != 0 && i != cmd_c)
			{
				close(fd[1]);
				dup2(fd[0], STDOUT_FILENO);
				ft_exe_single(gen, gen->env);
				printf("==[HERE2]==\n");
			}
			else
			{
				close(fd[0]);
				dup2(fd[1], STDIN_FILENO);
				ft_exe_single(gen, gen->env);
				printf("==[HERE3]==\n");
			}
		}
		else
		{
			while (!WIFEXITED(status) && !WIFSIGNALED(status))
				waitpid(pid, &status, WUNTRACED);
			printf("==[HERE4]==\n");
		}
		i++;
		parsed = parsed->next;
		printf("==[HERE5]==\n");
	}
	return (-1);
}

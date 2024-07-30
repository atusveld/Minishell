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
	if (parsed->redir_in)
		ft_red_in(parsed);
	if (ft_if_builtin(gen, parsed) == 0)
		return ;
	if (!parsed->next)
		gen->e_code = ft_exe_single(gen, gen->env);
	else
		gen->e_code = ft_exe_multi(gen, parsed, -1, 0);
	if (parsed->argv[1])
	{
		if (ft_strncmp(parsed->argv[1], "$?", 5) == 0)
		{
			ft_e_code(gen);
			return ;
		}
	}
}

int	ft_exe_single(t_gen *gen, t_env *env)
{
	pid_t	f_id;
	char 	**arr;
	char	*path;
	int		status;

	f_id = fork();
	status = -1;
	path = get_cmd_path(gen);
	arr = ft_env_to_array(env);
	if (f_id < 0)
		// ft_error("fork");
		exit (gen->e_code);
	if (f_id == 0)
	{
		execve(path, gen->cmd_args, arr);
		exit (gen->e_code);
		// ft_error("single cmd");
	}
	else
	{
		while (!WIFEXITED(status) && !WIFSIGNALED(status))
		{
			gen->e_code = ((status >> 8) & 0xFF);
			waitpid(f_id, &status, WUNTRACED);
		}
	}
	ft_free_arr(arr);
	return (gen->e_code);
}

int	ft_exe_multi(t_gen *gen, t_parse *parsed, int status, int i)
{
	t_pipe	*pipe;
	int		pid;
	int		cmd_c;

	cmd_c = ft_count_cmd(parsed);
	pipe = ft_init_pipes();
	while (cmd_c > i++)
	{
		pid = ft_fork();
		if (pid == 0)
			ft_fml(gen, pipe, i, cmd_c);
		else
		{
			close(pipe->tube[1]);
			if (waitpid(pid, &status, WUNTRACED) == -1)
				ft_error("waitpid multi");
			gen->e_code = ((status >> 8) & 0xFF);
		}
		if (parsed->next)
		{
			pipe->in_fd = pipe->tube[0];
			parsed = parsed->next;
		}
		gen->cmd_args = parsed->argv;
	}
	return (gen->e_code);
}
void	ft_e_code(t_gen *gen)
{
	ft_putnbr_fd(gen->e_code, 1);
	write(1, "\n", 1);
}
//-> ((status >> 8) 7 0xFF) return value calc <-

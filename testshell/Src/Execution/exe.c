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
	gen->e_code = 0;
	gen->owd = getcwd(NULL, 0);
	if (parsed->redir_in)
		ft_red_in(parsed, gen);
	if (parsed->redir_out)
		ft_red_out(parsed, gen);
	if (ft_if_builtin(gen, parsed) == 0)
		return ;
	if (!parsed->next)
		gen->e_code = ft_exe_single(gen, gen->env);
	else
		gen->e_code = ft_exe_multi(gen, parsed, -1, 0);
	// return ;
}

int	ft_exe_single(t_gen *gen, t_env *env)
{
	pid_t	pid;
	char 	**arr;
	char	*path;
	int		status;

	status = -1;
	path = get_cmd_path(gen);
	arr = ft_env_to_array(env);
	pid = fork();
	if (pid < 0)
		ft_error("fork single", gen);
	if (pid == 0)
	{
		if ((execve(path, gen->cmd_args, arr)) < 0)
			ft_error("single cmd", gen);
	}
	else
	{
		while (!WIFEXITED(status) && !WIFSIGNALED(status))
		{
			waitpid(pid, &status, WUNTRACED);
			gen->e_code = ((status >> 8) & 0xFF);
		}
	}
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
			{
				gen->e_code = ((status >> 8) & 0xFF);
				ft_error("wait multi", gen);
			}
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
	if (ft_isdigit(gen->e_code) != 1)
		ft_error("e_code not digit", gen);
	ft_putnbr_fd(gen->e_code, 1);
	write(1, "\n", 1);
	return ;
}
//-> ((status >> 8) 7 0xFF) return value calc <-

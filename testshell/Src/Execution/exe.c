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

#include "../../Includes/main.h"

void	ft_exe(t_parse *parsed, t_main *main)
{
<<<<<<< HEAD
	main->gen->cmd_args = parsed->argv;
	// if (parsed->argv)
		// gen->cmd_args = parsed->argv;
=======
>>>>>>> c3aecb263a7c5383cfc3f28adc8d242fac8f04ab
	if (parsed->redir_in)
		ft_red_in(parsed, main);
	if (parsed->redir_out)
		ft_red_out(parsed, main);
	if (ft_if_builtin(main, parsed) == 0)
		return ;
	if (!parsed->next)
		main->gen->e_code = ft_exe_single(main, main->env);
	else
		main->gen->e_code = ft_exe_multi(main, parsed, -1, 0);
	// return ;
}

int	ft_exe_single(t_main *main, t_env *env)
{
	pid_t	pid;
	char 	**arr;
	char	*path;
	int		status;

	status = -1;
	path = get_cmd_path(main);
	arr = ft_env_to_array(env);
	pid = fork();
	if (pid < 0)
		ft_error("fork single", main);
	if (pid == 0)
	{
		if ((execve(path, main->gen->cmd_args, arr)) < 0)
			ft_error("single cmd", main);
	}
	else
	{
		while (!WIFEXITED(status) && !WIFSIGNALED(status))
		{
			waitpid(pid, &status, WUNTRACED);
			main->gen->e_code = ((status >> 8) & 0xFF);
		}
	}
	return (main->gen->e_code);
}

int	ft_exe_multi(t_main *main, t_parse *parsed, int status, int i)
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
			ft_fml(main, pipe, i, cmd_c);
		else
		{
			close(pipe->tube[1]);
			if (waitpid(pid, &status, WUNTRACED) == -1)
			{
				main->gen->e_code = ((status >> 8) & 0xFF);
				ft_error("wait multi", main);
			}
		}
		if (parsed->next)
		{
			pipe->in_fd = pipe->tube[0];
			parsed = parsed->next;
		}
		main->gen->cmd_args = parsed->argv;
	}
	return (main->gen->e_code);
}
<<<<<<< HEAD
void	ft_e_code(t_main *main)
=======

void	ft_e_code(t_gen *gen)
>>>>>>> c3aecb263a7c5383cfc3f28adc8d242fac8f04ab
{
	if (ft_isdigit(main->gen->e_code) != 1)
		ft_error("e_code not digit", main);
	ft_putnbr_fd(main->gen->e_code, 1);
	write(1, "\n", 1);
	return ;
}
//-> ((status >> 8) 7 0xFF) return value calc <-

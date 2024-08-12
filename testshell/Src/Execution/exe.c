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
	main->gen->cmd_args = parsed->argv;
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
		ft_error("Fork failed", 1);
	if (pid == 0)
    {
        if ((execve(path, main->gen->cmd_args, arr)) < 0)
        {
            if (errno == EACCES)
                ft_error("Permission denied", 126);
            else
                ft_error("Command not found", 127);
        }
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
    t_pipe	*pipes;
    int		pid;
    int		cmd_c;

    cmd_c = ft_count_cmd(parsed);
    pipes = ft_init_pipes(cmd_c);
    while (cmd_c > i++)
    {
        pid = ft_fork();
        if (pid == 0)
            ft_dup_exe(main, pipes, i, cmd_c);
        else
        {
            if (i > 1)
                close(pipes[i - 2].tube[0]);
            close(pipes[i - 1].tube[1]);
            if (waitpid(pid, &status, WUNTRACED) == -1)
            {
                main->gen->e_code = ((status >> 8) & 0xFF);
				return (main->gen->e_code);
            }
            else
                main->gen->e_code = WEXITSTATUS(status);
        }
        if (parsed->next)
        {
            pipes[i - 1].in_fd = pipes[i - 1].tube[0];
            parsed = parsed->next;
        }
        main->gen->cmd_args = parsed->argv;
    }
    return (main->gen->e_code);
}


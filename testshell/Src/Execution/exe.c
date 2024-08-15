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
	char	**arr;
	char	*path;

	main->gen->cmd_args = parsed->argv;
	path = get_cmd_path(main);
	arr = ft_env_to_array(main->env);
	if (parsed->redir_in)
		ft_red_in(parsed);
	if (parsed->redir_out)
		ft_red_out(parsed);
	if (ft_if_builtin(main, parsed) == 0)
		return ;
	if (!parsed->next)
		main->gen->e_code = ft_exe_single(main, path, arr);
	else
		main->gen->e_code = ft_exe_multi(main, parsed, -1);
}

int	ft_exe_single(t_main *main, char *path, char **arr)
{
	pid_t	pid;
	int		status;

	status = -1;
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
			waitpid(pid, &status, WUNTRACED);
		main->gen->e_code = ((status >> 8) & 0xFF);
	}
	return (main->gen->e_code);
}

int	ft_exe_multi(t_main *main, t_parse *parsed, int status)
{
	t_pipe	*pipes;
	int		*pids;
	int		cmd_c;
	int		j;

	j = 0;
	cmd_c = ft_init_pipes_pids(parsed, &pipes, &pids);
	if (cmd_c == -1)
		return (-1);
	ft_fork_exe(main, parsed, pipes, pids, cmd_c);
	while (j < cmd_c)
	{
		if (waitpid(pids[j], &status, WUNTRACED) == -1)
		{
			main->gen->e_code = ((status >> 8) & 0xFF);
			free(pids);
			free(pipes);
			return (main->gen->e_code);
		}
		main->gen->e_code = WEXITSTATUS(status);
		j++;
	}
	free(pids);
	free(pipes);
	return (main->gen->e_code);
}

int	ft_init_pipes_pids(t_parse *parsed, t_pipe **pipes, int **pids)
{
	int	cmd_c;

	cmd_c = ft_count_cmd(parsed);
	*pipes = ft_init_pipes(cmd_c);
	*pids = malloc(sizeof(int) * cmd_c);
	if (!*pids)
	{
		free(*pipes);
		return (-1);
	}
	return (cmd_c);
}

void	ft_fork_exe(t_main *main, t_parse *parsed, t_pipe *pipes, int *pids, int cmd_c)
{
	int	pid;
	int	i;

	pid = 0;
	i = 0;
	while (cmd_c > i++)
	{
		pid = ft_fork();
		if (pid < 0)
		{
			ft_error("Fork failed", 1);
			return ;
		}
		if (pid == 0)
		{
			close_pipes(pipes, cmd_c, i);
			ft_dup_exe(main, pipes, i, cmd_c);
			exit(main->gen->e_code);
		}
		else
		{
			pids[i - 1] = pid;
			if (i > 1)
				close(pipes[i - 2].tube[0]);
			if (i < cmd_c)
				close(pipes[i - 1].tube[1]);
		}
		if (parsed->next)
			parsed = parsed->next;
		main->gen->cmd_args = parsed->argv;
	}
}

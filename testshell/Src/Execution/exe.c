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

#include "../../Includes/shell.h"

void	ft_exe(t_parse *parsed, t_shell *shell)
{
	char	**arr;
	char	*path;

	shell->gen->cmd_args = parsed->argv;
	path = get_cmd_path(shell);
	arr = ft_env_to_array(shell->env);
	if (arr == NULL)
		ft_error_ne("Error creating environment array, exe", shell, 1);
	if (parsed->redir_in)
		ft_red_in(shell);
	if (parsed->redir_out)
		ft_red_out(shell);
	if (!parsed->next)
	{
		if (ft_if_builtin(shell) == 0)
			return ;
		shell->gen->e_code = ft_exe_single(shell, path, arr);
	}
	else
		shell->gen->e_code = ft_exe_multi(shell, parsed, -1);
	ft_free_arr(arr);
	free(path);
}

int	ft_exe_single(t_shell *shell, char *path, char **arr)
{
	pid_t	pid;
	int		status;

	status = -1;
	pid = fork();
	if (pid < 0)
		ft_error("Fork failed, single", shell, 1);
	if (pid == 0)
	{
		if ((execve(path, shell->gen->cmd_args, arr)) < 0)
		{
			if (errno == EACCES)
				ft_error("Permission denied, single cmd", shell, 126);
			else
				ft_error("Command not found, single cmd", shell, 127);
		}
	}
	else
	{
		while (!WIFEXITED(status) && !WIFSIGNALED(status))
			waitpid(pid, &status, WUNTRACED);
		shell->gen->e_code = ((status >> 8) & 0xFF);
	}
	return (shell->gen->e_code);
}

int	ft_exe_multi(t_shell *shell, t_parse *parsed, int status)
{
	t_pipe	*pipes;
	int		*pids;
	int		cmd_c;
	int		j;

	j = 0;
	if (ft_if_builtin(shell) == 0)
		return (shell->gen->e_code);
	cmd_c = ft_init_pipes_pids(shell, &pipes, &pids);
	if (cmd_c == -1)
		return (-1);
	ft_fork_exe(shell, parsed, pipes, pids, cmd_c);
	while (j < cmd_c)
	{
		if (waitpid(pids[j], &status, WUNTRACED) == -1)
		{
			shell->gen->e_code = ((status >> 8) & 0xFF);
			free(pids);
			free(pipes);
			return (shell->gen->e_code);
		}
		shell->gen->e_code = WEXITSTATUS(status);
		j++;
	}
	free(pids);
	free(pipes);
	return (shell->gen->e_code);
}

int	ft_init_pipes_pids(t_shell *shell, t_pipe **pipes, int **pids)
{
	int	cmd_c;

	cmd_c = ft_count_cmd(shell->parsed);
	*pipes = ft_init_pipes(shell, cmd_c);
	*pids = malloc(sizeof(int) * cmd_c);
	if (!*pids)
	{
		free(*pipes);
		return (-1);
	}
	return (cmd_c);
}

void	ft_fork_exe(t_shell *shell, t_parse *parsed, t_pipe *pipes, int *pids, int cmd_c)
{
	int	pid;
	int	i;

	pid = 0;
	i = 0;
	while (cmd_c > i++)
	{
		pid = ft_fork(shell);
		if (pid < 0)
		{
			ft_error("Fork failed", shell, 1);
			return ;
		}
		if (pid == 0)
		{
			close_pipes(pipes, cmd_c, i);
			ft_dup_exe(shell, pipes, i, cmd_c);
			exit(shell->gen->e_code);
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
		shell->gen->cmd_args = parsed->argv;
	}
}

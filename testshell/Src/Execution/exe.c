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

int	new_process(t_gen *gen, char **n_envp)
{
	int		status;
	pid_t	pid;

	pid = fork();
	status = -1;
	if (pid == 0)
	{
		if ((execve(gen->cmd_path, gen->cmd_args, n_envp)) == -1)
		{
			perror ("child error");
			exit (EXIT_FAILURE);
		}
	}
	else if (pid < 0)
	{
		perror ("fork fail");
		exit(1);
	}
	else
	{
		while (!WIFEXITED(status) && !WIFSIGNALED(status))
			waitpid(pid, &status, WUNTRACED);
	}
	return (-1);
}

char	**get_paths(t_gen *gen) //looks into own env for paths in order to execute
{
	char	*tmp;
	char	**paths;

	gen->env->val = ft_get_env(gen->env, "PATH");
	tmp = gen->env->val;
	if (!tmp)
	{
		if (access(gen->cmd_args[0], X_OK) == -1)
			exit (127);
		return (NULL);
	}
	paths = ft_split(tmp, ':');
	if (!paths)
		ft_error("split");
	return (paths);
}

char	*get_cmd_path(t_gen *gen) //finds command path in env for execve
{
	char	*cmd_path;
	char	*tmp_cmd;
	int		i;
	
	i = 0;
	tmp_cmd = ft_strjoin("/", gen->cmd_args[0]);
	if (!tmp_cmd)
		ft_error("strjoin");
	while (gen->env_paths[i])
	{
		cmd_path = ft_strjoin(gen->env_paths[i], tmp_cmd);
		if (!cmd_path)
			ft_error("strjoin");
		if (access(cmd_path, X_OK) == 0)
		{
			free (tmp_cmd);
			return (cmd_path);
		}
		free (cmd_path);
		i++;
	}
	free (tmp_cmd);
	return (NULL);
}

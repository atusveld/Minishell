/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                      	                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: atusveld <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/03 15:26:55 by atusveld      #+#    #+#                 */
/*   Updated: 2022/09/07 17:40:34 by atusveld      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**get_paths(t_gen *gen)
{
	char	*tmp;
	char	**paths;

	// tmp = getenv("PATH");
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

char	*get_cmd_path(t_gen *gen)
{
	char	*cmd_path;
	char	*tmp_cmd;
	int		i;
	
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

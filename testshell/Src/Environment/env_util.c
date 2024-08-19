/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_util.c                      	                :+:    :+:            */
/*                                                     +:+                    */
/*   By: atusveld <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/03 15:26:55 by atusveld      #+#    #+#                 */
/*   Updated: 2022/09/07 17:40:34 by atusveld      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	**ft_env_to_array(t_env *env)
{
	char	**arr;
	t_env	*temp;
	int		i;

	i = 0;
	temp = env;
	while (temp)
	{
		temp = temp->next;
		i++;
	}
	arr = (char **)malloc((i + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	arr[i] = NULL;
	i--;
	temp = env;
	while (i >= 0)
	{
		arr[i] = ft_strdup(temp->str);
		if (!arr[i])
		{
			ft_free_arr(arr);
			return (NULL);
		}
		temp = temp->next;
		i--;
	}
	return (arr);
}

char	**get_paths(t_shell *shell)
{
	char	*temp;
	char	**paths;

	if (!shell->env)
	{
		ft_error("Error getting paths, get_paths", shell, 1);
		return (NULL);
	}
	temp = ft_get_env(shell->env, "PATH");
	// if(!temp)
	// {
	// 	ft_error("PATH not found", shell, 1);
	// 	return (NULL);
	// }
	if (!temp)
	{
		if (access(shell->gen->cmd_args[0], X_OK) == -1)
			ft_error("Command not found", shell, 127);
		return (NULL);
	}
	paths = ft_split(temp, ':');
	return (paths);
}

char	*get_cmd_path(t_shell *shell)
{
	char	*cmd_path;
	char	*tmp_cmd;
	int		i;

	i = 0;
	if(!shell->gen->cmd_args)
		ft_error("Error getting command path, get_cmd_path", shell, 1);
	tmp_cmd = ft_strjoin("/", shell->gen->cmd_args[0]);
	if (!tmp_cmd)
	{
		free(tmp_cmd);
		ft_error("Error creating command path, get_cmd_path", shell, 1);
	}
	while (shell->gen->env_paths[i])
	{
		cmd_path = ft_strjoin(shell->gen->env_paths[i], tmp_cmd);
		if (!cmd_path)
		{
			free(tmp_cmd);
			ft_error("Error creating command path, get_cmd_path", shell, 1);
		}
		if (access(cmd_path, X_OK) == 0)
		{
			free (tmp_cmd);
			return (cmd_path);
		}
		free (cmd_path);
		i++;
	}
	free(tmp_cmd);
	return (NULL);
}

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
	arr[i] = NULL;
	i--;
	temp = env;
	while (i >= 0)
	{
		arr[i] = ft_strdup(temp->str);
		temp = temp->next;
		i--;
	}
	return (arr);
}

char	**get_paths(t_shell *shell)
{
	char	*temp;
	char	**paths;

	shell->env->val = ft_get_env(shell->env, "PATH");
	if(!shell->env->val)
	{
		ft_error("PATH not found", shell, 1);
		return (NULL);
	}
	temp = shell->env->val;
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
	if (shell->gen->cmd_args)
		tmp_cmd = ft_strjoin("/", shell->gen->cmd_args[0]);
	while (shell->gen->env_paths[i])
	{
		cmd_path = ft_strjoin(shell->gen->env_paths[i], tmp_cmd);
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

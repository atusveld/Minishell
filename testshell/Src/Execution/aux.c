/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   aux.c                      	                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: atusveld <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/03 15:26:55 by atusveld      #+#    #+#                 */
/*   Updated: 2022/09/07 17:40:34 by atusveld      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/shell.h"

char	*ft_strjoin_three(char *s1, char *s2, char *s3)
{
	char	*temp;
	char	*str;

	temp = ft_strjoin(s1, s2);
	if (!temp)
		return (NULL);
	str = ft_strjoin(temp, s3);
	if (!str)
	{
		free (temp);
		temp = NULL;
		return (NULL);
	}
	free (temp);
	return (str);
}

void	*ft_free_arr(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return (NULL);
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
	arr = NULL;
	return (NULL);
}

int	ft_count_cmd(t_parse *parsed)
{
	t_parse	*tmp;
	int		i;

	i = 0;
	tmp = parsed;
	while (tmp != NULL)
	{
		tmp = tmp->next;
		i++;
	}
	free(tmp);
	return (i);
}

t_pipe	*ft_init_pipes(t_shell *shell, int cmd_count)
{
    t_pipe	*pipes;
    int		i;

    pipes = malloc(sizeof(t_pipe) * (cmd_count - 1));
    if (!pipes)
        return (NULL);
    i = 0;
    while (i < cmd_count - 1)
    {
        if (pipe(pipes[i].tube) == -1)
        {
			free(pipes);
			pipes = NULL;
			ft_error("pipe failed", shell, 1);
		}
        i++;
    }
    return (pipes);
}

void	ft_free_gen(t_shell *shell)
{
	ft_free_env(&shell->env);
	if (shell->gen->cmd_args)
		ft_free_arr(shell->gen->cmd_args);
	if (shell->gen->env_paths)
		ft_free_arr(shell->gen->env_paths);
	if (shell->gen->cmd_path)
		free(shell->gen->cmd_path);
}

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

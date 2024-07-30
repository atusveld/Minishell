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

#include "../../Includes/alex.h"

char	*ft_strjoin_three(char *s1, char *s2, char *s3)
{
	char	*temp;
	char	*str;

	temp = ft_strjoin(s1, s2);
	if (!temp)
		ft_error("strj3");
	str = ft_strjoin(temp, s3);
	if (!str)
		ft_error("strj3");
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
		i++;
	}
	free(arr);
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

t_pipe	*ft_init_pipes(void)
{
	t_pipe	*new_pipe;

	new_pipe = (t_pipe *)malloc(sizeof(t_pipe));
	if (!new_pipe)
		ft_error("init pipes");
	pipe(new_pipe->tube);
	new_pipe->in_fd = STDIN_FILENO;
	return (new_pipe);
}

void	ft_free_gen(t_gen *gen)
{
	ft_free_env(&gen->env);
	ft_free_arr(gen->cmd_args);
	ft_free_arr(gen->env_paths);
	free(gen->cmd_path);
}

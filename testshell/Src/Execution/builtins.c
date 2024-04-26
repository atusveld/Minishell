/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: atusveld <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/03 15:26:55 by atusveld      #+#    #+#                 */
/*   Updated: 2022/09/07 17:40:34 by atusveld      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/alex.h"

int	ft_if_builtin(t_gen *gen)
{
	if (!ft_strncmp(gen->cmd_args[0], "echo", 5))
		return (ft_echo(gen->cmd_args + 1), 0);
	if (!ft_strncmp(gen->cmd_args[0], "pwd", 4))
		return (ft_pwd(), 0);
	if (!ft_strncmp(gen->cmd_args[0], "env", 4))
		return (ft_env(gen), 0);
	return (1);
}
void	ft_echo(char **arr)
{
	bool nl;

	nl = true;
	if (!ft_strncmp(arr[0], "-n", 3))
	{
		nl = false;
		arr++;
	}
	while (*arr)
	{
		ft_putstr_fd(*arr, 1);
		if (*(arr + 1) && **arr)
			ft_putchar_fd(' ', 1);
		arr++;
	}
	if (nl)
		ft_putchar_fd('\n', 1);
}
void	ft_pwd(void)
{
	char	*temp;

	temp = getcwd(NULL, 0);
	printf("%s\n", temp);
	free (temp);
}
void	ft_env(t_gen *gen)
{
	printf("%s\n", gen->env->str);
}

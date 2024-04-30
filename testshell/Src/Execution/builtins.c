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

// cd working, exit, export, unset

int	ft_if_builtin(t_gen *gen)
{
	if (!ft_strncmp(gen->cmd_args[0], "echo", 5))
		return (ft_echo(gen->cmd_args + 1), 0);
	if (!ft_strncmp(gen->cmd_args[0], "pwd", 4))
		return (ft_pwd(), 0);
	if (!ft_strncmp(gen->cmd_args[0], "env", 4))
		return (ft_env(gen), 0);
	if (!ft_strncmp(gen->cmd_args[0], "cd", 3))
		return (ft_cd(gen), 0);
	return (1);
}
void	ft_echo(char **arr)
{
	bool nl;

	nl = true;
	if (!*arr)
		*arr = NULL;
	else if (!ft_strncmp(arr[0], "-n", 3))
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

void	ft_cd(t_gen *gen)
{
	char	*old_p;
	char	*new_p;
	char	*path;

	path = ft_strjoin_three(getcwd(NULL, 0), "/", gen->cmd_args[1]);
	if (!path || !*path)
		path = ft_get_env(gen->env, "HOME");
	old_p = getcwd(NULL, 0);
	chdir(path);
	new_p = getcwd(NULL, 0);
	ft_cd_update_env(gen, old_p, new_p);
	free (old_p);
	free (new_p);
}

void	ft_cd_update_env(t_gen *gen, char *old_p, char *new_p)
{
	if (ft_find_env(gen->env, "OLD_PWD"))
		ft_add_envtry(gen->env, "OLD_PWD", old_p);
	if (ft_find_env(gen->env, "NEW_PWD"))
		ft_add_envtry(gen->env, "NEW_PWD", new_p);
}

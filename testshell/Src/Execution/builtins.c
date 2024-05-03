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

//exit, export to come. they are not perfect yet (protection etc) lmk what u need

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
	if (!ft_strncmp(gen->cmd_args[0], "exit", 5))
		return (ft_exit(), 0);
	if (!ft_strncmp(gen->cmd_args[0], "unset", 6))
		return (ft_unset(gen->env, gen->cmd_args + 1), 0);
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
	t_env	*temp;

	temp = gen->env;
	while (temp)
	{
		if (temp->val && temp->key)
			printf("%s\n", temp->str);
		temp = temp->next;
	}
}

void	ft_cd(t_gen *gen)
{
	char	*old_p;
	char	*new_p;
	char	*path;
	
	old_p = getcwd(NULL, 0);
	path = ft_strjoin_three(old_p, "/", gen->cmd_args[1]);
	if (!path || !*path)
		path = ft_get_env(gen->env, "HOME"); // might want to set home to home of minishell project instead of home  of user
	if (chdir(path) == -1)
		perror("cd");
	new_p = getcwd(NULL, 0);
	ft_cd_update_env(gen, old_p, new_p);
	free (old_p);
	free (new_p);
	free (path);
}

void	ft_cd_update_env(t_gen *gen, char *old_p, char *new_p)
{
	if (ft_find_env(gen->env, "OLD_PWD"))
		ft_add_envtry(gen->env, "OLD_PWD", old_p);
	if (ft_find_env(gen->env, "NEW_PWD"))
		ft_add_envtry(gen->env, "NEW_PWD", new_p);
}
void	ft_exit(void) // check if first and last cmd per prompt -> no forky etc
{
	int	status;

	status = 0;
	exit(status);
}
static int	ft_unset_error(char *arg, char *msg)
{
	ft_putstr_fd("minishell: unset: `", 2);
	if (arg)
		ft_putchar_fd(*arg, 2);
	if (msg)
		ft_putchar_fd(*msg, 2);
	return (1);
}
static bool		ft_check_var(char *str)
{
	if (ft_isdigit(*str))
		return (false);
	while (*str && (*str == '_' || ft_isalnum(*str)))
		str++;
	if (!*str)
		return (true);
	return (false);
}
int	ft_unset(t_env *env, char **argv)
{
	int	i;

	i = 1;
	while (&argv[i])
	{
		if (ft_check_var(argv[i]) == false)
			ft_unset_error(argv[i], "': not a valid identifier\n");
		else
			ft_unset_env(&env, argv[i]);
		i++;
	}
	return (1);
}



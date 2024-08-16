/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins_unset.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: atusveld <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/03 15:26:55 by atusveld      #+#    #+#                 */
/*   Updated: 2024/08/06 16:34:48 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	ft_unset_error(char *arg, char *msg)
{
	ft_putstr_fd("minishell: unset: `", 2);
	if (arg)
		ft_putchar_fd(*arg, 2);
	if (msg)
		ft_putchar_fd(*msg, 2);
	return (1);
}

static bool	ft_check_var(char *str)
{
	if (!str || ft_isdigit(*str) == 1)
		return (false);
	while (*str && (*str == '_' || ft_isalnum(*str)))
		str++;
	if (!*str)
		return (true);
	return (false);
}

void	ft_unset_env(t_shell *shell, char *key)
{
	t_env	*val;

	if (!shell || !key)
		ft_error("unset", shell, 1);
	val = ft_find_env(shell->env, key);
	if (!val)
		ft_error("unset", shell, 1);
	ft_del_env(&shell->env, val);
}

int	ft_unset(t_shell *shell, char **argv)
{
	int	i;

	if (!shell || !argv)
        return (1);
	i = 1;
	if (!argv[i])
		ft_error("unset", shell, 1);
	while (argv[i])
	{
		if (ft_check_var(argv[i]) == false)
			ft_unset_error(argv[i], "': not a valid identifier\n");
		else
			ft_unset_env(shell, argv[i]);
		i++;
	}
	return (1);
}

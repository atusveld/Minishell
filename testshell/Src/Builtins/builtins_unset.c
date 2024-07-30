/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins_unset.c                                    :+:    :+:           */
/*                                                     +:+                    */
/*   By: atusveld <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/03 15:26:55 by atusveld      #+#    #+#                 */
/*   Updated: 2022/09/07 17:40:34 by atusveld      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/alex.h"

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
void	ft_unset_env(t_env **env, char *key)
{
	t_env	*keyval;

	if (!key)
		return ;
	keyval = ft_find_env(*env, key);
	if (!keyval)
		return ;
	ft_del_env(env, keyval);
}
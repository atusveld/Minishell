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

#include "main.h"

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
	if (ft_isdigit(*str) == 1)
		return (false);
	while (*str && (*str == '_' || ft_isalnum(*str)))
		str++;
	if (!*str)
		return (true);
	return (false);
}

<<<<<<< HEAD
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

int	ft_unset(t_env *env, char **argv)
=======
int	ft_unset(t_gen *gen, char **argv)
>>>>>>> c3aecb263a7c5383cfc3f28adc8d242fac8f04ab
{
	int	i;

	i = 0;
	if (!argv[i])
		ft_error("unset, invalid arg", gen);
	while (argv[i])
	{
		if (ft_check_var(argv[i]) == false)
			ft_unset_error(argv[i], "': not a valid identifier\n");
		else
			ft_unset_env(gen, argv[i]);
		i++;
	}
	return (1);
}
<<<<<<< HEAD
=======
void	ft_unset_env(t_gen *gen, char *key)
{
	t_env	*val;

	if (!key)
		return ;
	val = ft_find_env(gen->env, key);
	if (!val)
		return ;
	ft_del_env(&gen->env, val);
}
>>>>>>> c3aecb263a7c5383cfc3f28adc8d242fac8f04ab

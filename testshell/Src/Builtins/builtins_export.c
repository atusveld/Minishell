/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins_export.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: atusveld <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/03 15:26:55 by atusveld      #+#    #+#                 */
/*   Updated: 2024/08/08 17:31:07 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static bool	ft_check_var(char *str)
{
	if (!*str || ft_isdigit(*str))
		return (false);
	while (*str && (*str == '_' || ft_isalnum(*str)))
		str++;
	if (!*str)
		return (true);
	return (false);
}

static void	ft_export_add_env(t_env **env, char *str)
{
	char	*key;
	char	*val;
	int		i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (!i)
		i++;
	key = ft_substr(str, 0, i);
	val = NULL;
	if (ft_check_var(key) == true)
	{
		if (str[i])
			val = ft_strdup(&str[i + 1]);
		ft_add_envtry(*env, key, val);
		free(val);
	}
	// else
	// 	ft_error("export, no valid identifier");
	free(key);
}

<<<<<<< HEAD
int	ft_export(t_main *main)
=======
int	ft_export(t_gen *gen, char **argv)
>>>>>>> c3aecb263a7c5383cfc3f28adc8d242fac8f04ab
{
	int	i;

<<<<<<< HEAD
	i = 1;
	argv = (main->gen->cmd_args + 1);
=======
	i = 0;
	if (!argv[i])
		ft_error("export arg invalid", gen);
>>>>>>> c3aecb263a7c5383cfc3f28adc8d242fac8f04ab
	while (argv[i] && !*argv[i])
		i++;
	if (!argv[i])
		return (ft_export_print(ft_env_to_array(main->env)));
	while (argv[i])
	{
		if (*argv[i])
			ft_export_add_env(&main->env, argv[i]);
		i++;
	}
	return (1);
}

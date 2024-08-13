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
	else
	{
		free(key);
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
	}
	free(key);
}

int	ft_export(t_main *main)
{
	char **argv;
	int	i;

	i = 1;
	argv = (main->gen->cmd_args + 1);
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

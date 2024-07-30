/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins_export.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: atusveld <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/03 15:26:55 by atusveld      #+#    #+#                 */
/*   Updated: 2024/05/20 11:13:11 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/alex.h"

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
		ft_error("export, no valid identifier");
	free(key);
}

int	ft_export(t_env **env, char **argv)
{
	int	i;

	i = 1;
	while (argv[i] && !*argv[i])
		i++;
	if (!argv[i])
		return (ft_export_print(ft_env_to_array(*env)));
	while (argv[i])
	{
		if (*argv[i])
			ft_export_add_env(env, argv[i]);
		i++;
	}
	return (1);
}

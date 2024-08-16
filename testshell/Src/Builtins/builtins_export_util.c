/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins_export_util.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: atusveld <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/03 15:26:55 by atusveld      #+#    #+#                 */
/*   Updated: 2024/08/06 14:23:10 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/shell.h"

static int	ft_max_strlen(char *s1, char *s2)
{
	int	len1;
	int	len2;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (len1 > len2)
		return (len1);
	return (len2);
}

static void	ft_arr_swap(char **s1, char **s2)
{
	char	*temp;

	temp = *s1;
	*s1 = *s2;
	*s2 = temp;
}

static void	ft_export_sort(char **env)
{
	int	i;
	int	j;

	if (!env)
		exit (EXIT_FAILURE);
	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[j] && env[j + 1])
		{
			if (ft_strncmp(env[j], env[j + 1],
					ft_max_strlen(env[j], env[j + 1]) + 1) > 0)
				ft_arr_swap(&env[j], &env[j + 1]);
			j++;
		}
		i++;
	}
}

static void	ft_export_printf(char *str)
{
	char	*key;
	char	*val;
	int		i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	key = ft_substr(str, 0, i + 1);
	if (str[i])
	{
		val = ft_strdup(&str[i + 1]);
		printf("declare -x%s\"%s\"\n", key, val);
		free(val);
	}
	else
		printf("declare -x %s\n", key);
	free(key);
}

int	ft_export_print(char **env)
{
	int	i;

	i = 0;
	ft_export_sort(env);
	while (env[i])
	{
		ft_export_printf(env[i]);
		i++;
	}
	ft_free_arr(env);
	return (1);
}

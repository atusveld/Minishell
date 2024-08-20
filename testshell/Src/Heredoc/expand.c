/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jovieira <jovieira@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/20 14:40:18 by jovieira      #+#    #+#                 */
/*   Updated: 2024/08/20 15:42:32 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	expand_error(char *str)
{
	perror(str);
	exit(1);
}

static char	*expand_str(char *def, char *val, int i, int j)
{
	char	*str;
	int		k;

	k = 0;
	(void)j;
	str = ft_calloc(j + 1, sizeof(char));
	if (!str)
		expand_error("Malloc failed in expand, quiting minishell");
	while (def[k] != '$')
		k++;
	ft_memcpy(str, def, k);
	ft_memcpy(str + k, val, ft_strlen(val));
	ft_memcpy(str + k + ft_strlen(val), def + k + i, ft_strlen(def + k + i));
	return (str);
}

static char	*find_env_val(t_env *tmp_env, char *str, int i)
{
	while (tmp_env)
	{
		if (!ft_strncmp(str + 1, tmp_env->key, i))
			return (ft_strdup(tmp_env->val));
		tmp_env = tmp_env->next;
	}
	return(ft_strdup(""));
}

static char	*find_e_code(t_shell *shell, char *str)
{
	char *val;
	char *val_tmp;
	int	i;

	i = 0;
	val = ft_itoa(shell->gen->e_code);
	val_tmp = ft_strjoin(val, str + 2);
	free(val);
	return (val_tmp);
}

char	*expandable(char *def, t_shell *shell)
{
	char *str;
	char *val;
	char tmp;
	int	j;
	int	i;

	val = NULL;
	str = ft_strchr(def, '$');
	if (!str)
		return (def);
	i = 1;
	while (str[i] != '\0' && (ft_isalnum(str[i]) || str[i] == '?'))
		i++;
	tmp = str[i];
	str[i] = '\0';
	if (str[1] == '?')
		val = find_e_code(shell, str);
	else
		val = find_env_val(shell->env, str, i);
	str[i] = tmp;
	j = ft_strlen(def) + ft_strlen(val) - i;
	str = expand_str(def, val, i, j);
	free(val);
	return(str);
}

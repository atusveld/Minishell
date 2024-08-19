/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jovieira <jovieira@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/20 14:40:18 by jovieira      #+#    #+#                 */
/*   Updated: 2024/08/19 15:06:40 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	*expand_str(char *def, char *val, int i, int j)
{
	char	*str;
	int		k;

	k = 0;
	str = ft_calloc(j + 1, sizeof(char));
	if (!str)
		exit (1); // add error msg
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
			return (tmp_env->val);
		tmp_env = tmp_env->next;
	}
	return("");
}

static char	*find_e_code(t_shell *shell)
{
	char *str;
	char *val;

	str = ft_itoa(shell->gen->e_code);
	val = str;
	free(str);
	return (str);
}

char	*expandable(char *def, t_shell *shell)
{
	char *str;
	char *val;
	char tmp;
	int	j;
	int	i;

	str = ft_strchr(def, '$');
	if (!str)
		return (def);
	i = 1;
	while (str[i] != '\0' && (ft_isalnum(str[i]) || str[i] == '?'))
		i++;
	tmp = str[i];
	str[i] = '\0';
	if (str[1] == '?')
		val = find_e_code(shell);
	else
		val = find_env_val(shell->env, str, i);
	str[i] = tmp;
	j = ft_strlen(def) + ft_strlen(val) - i;
	str = expand_str(def, val, i, j);
	return(str);
}
// val = ft_itoa(shell->gen->e_code); // needs to be fixed allowing extra text after $? plus leak fix
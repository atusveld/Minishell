/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jovieira <jovieira@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/20 14:40:18 by jovieira      #+#    #+#                 */
/*   Updated: 2024/07/09 11:07:02 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/main.h"

// def = stands for default
char	*expandable(char *def, t_env *tmp_env)
{
	char *str;
	char *val;
	int	j;

	val = "";
	str = ft_strchr(def, '$');
	while (tmp_env)
	{
		if (!ft_strcmp(str + 1, tmp_env->key))
		{
			val = tmp_env->val;
			break ;
		}
		tmp_env = tmp_env->next;
	}
	j = ft_strchr(str, ' ') - str;
	return(val);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expansion_utils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jovieira <jovieira@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/06 11:01:05 by jovieira      #+#    #+#                 */
/*   Updated: 2024/08/06 17:08:12 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

char	*end_expand(t_token *token, t_exp *exp_data)
{
	if (!ft_strlen(token->cont))
	{
		token->cont = ft_strdup(exp_data->tmp_str);
		free (exp_data->tmp_str);
		if (exp_data->tmp_exp)
			free (exp_data->tmp_exp);
		if (!token->next)
			free(exp_data);
	}
	return (token->cont);
}

t_exp	*exp_init(t_exp *exp_data)
{
	exp_data = malloc(sizeof(t_exp));
	exp_data->tmp_str = ft_strdup("");
	exp_data->tmp_exp = ft_strdup("");
	return (exp_data);
}

void	tmp_join(t_exp *exp_data, t_token *token, t_env *tmp_env, int action)
{
	if (action == 1)
	{
		exp_data->tmp_exp = ft_substr(token->cont, 0, exp_data->i);
		ft_memmove (token->cont, token->cont + exp_data->i, \
		ft_strlen(token->cont));
		exp_data->tmp_exp = expandable(exp_data->tmp_exp, tmp_env);
		exp_data->tmp_str = ft_strjoin(exp_data->tmp_str, \
		exp_data->tmp_exp);
	}
	else
	{
		exp_data->tmp_exp = ft_substr(token->cont, 0, exp_data->i);
		exp_data->tmp_exp = expandable(exp_data->tmp_exp, tmp_env);
		ft_memmove (token->cont, token->cont + exp_data->i, \
		ft_strlen(token->cont));
		exp_data->tmp_str = ft_strjoin(exp_data->tmp_str, \
		exp_data->tmp_exp);
	}
}

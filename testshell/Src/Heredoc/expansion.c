/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expansion.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jovieira <jovieira@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/24 12:28:07 by jovieira      #+#    #+#                 */
/*   Updated: 2024/08/06 11:36:30 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
// condition compare
static bool	comp(char *str, char del, char ex_del, int action)
{
	if (action == 1)
		return (ft_strlen_def(str, del) > ft_strlen_def(str, ex_del));
	else
		return (ft_strlen_def(str, del) < ft_strlen_def(str, ex_del));
}

// char	e_code_exp(char *str)
// {
// 	if (ft_strncmp(str, "$?", 1) == 0)
// 		return ('?');
// }

static bool	single_quote(t_token *token, t_exp *exp_data)
{
	if (comp(token->cont, '\'', '"', 0) && comp(token->cont, '\'', '$', 0))
	{
		exp_data->i = ft_strlen_def(token->cont, '\'');
		exp_data->i = skip_quotes(token->cont, exp_data->i);
		exp_data->tmp_str = ft_strjoin(exp_data->tmp_str, \
		ft_substr(token->cont, 0, exp_data->i + 1));
		ft_memmove (token->cont, token->cont + exp_data->i + 1, \
		ft_strlen(token->cont));
		return (true);
	}
	return (false);
}

// +1 in skip_char " to include the quote
static bool	double_quote(t_token *token, t_exp	*exp_data, t_env *tmp_env)
{
	if (comp(token->cont, '"', '\'', 0) && comp(token->cont, '"', '$', 0))
	{
		exp_data->in_quotes = true;
		while (comp(token->cont, '"', '\'', 0) || exp_data->in_quotes == true)
		{
			exp_data->i = ft_strlen_def(token->cont, '$');
			if (token->cont[exp_data->i] == '\0')
				return (false);
			if (comp(token->cont + exp_data->i + 1, '$', '"', 1))
			{
				exp_data->i = skip_char(token->cont, '"') + 1;
				exp_data->in_quotes = false;
			}
			else
				exp_data->i += skip_char(token->cont + exp_data->i, '$');
			tmp_join(exp_data, token, tmp_env, 1);
		}
		return (true);
	}
	return (false);
}

static bool	dollar_expand(t_token *token, t_exp *exp_data, t_env *tmp_env)
{
	if (ft_strchr(token->cont, '$'))
	{
		while (comp(token->cont, '$', '\'', 0) \
			&& comp(token->cont, '$', '"', 0))
		{
			exp_data->i = ft_strlen_def(token->cont, '$');
			if (comp(token->cont, '$', '\'', 0) \
				&& comp(token->cont, '$', '"', 0))
			{
				if (comp(token->cont + exp_data->i + 1, '$', '"', 1))
					exp_data->i = skip_char(token->cont, '"');
				else if (comp(token->cont + exp_data->i + 1, '$', '\'', 1))
					exp_data->i = skip_char(token->cont, '\'');
				else
					exp_data->i += skip_char(token->cont + exp_data->i, '$');
			}
			tmp_join(exp_data, token, tmp_env, 0);
		}
		return (true);
	}
	return (false);
}

void	token_expand(t_token *token, t_env *tmp_env)
{
	t_exp	*exp_data;

	exp_data = NULL;
	exp_data = exp_init(exp_data);
	while (token)
	{
		exp_data->in_quotes = false;
		if (single_quote(token, exp_data))
			continue ;
		if (double_quote(token, exp_data, tmp_env))
			continue ;
		if (dollar_expand(token, exp_data, tmp_env))
			continue ;
		token->cont = end_expand(token->cont, exp_data);
		token = token->next;
	}
}

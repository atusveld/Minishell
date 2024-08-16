/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expansion.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jovieira <jovieira@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/24 12:28:07 by jovieira      #+#    #+#                 */
/*   Updated: 2024/08/13 16:23:19 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
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
static bool	double_quote(t_main *main, t_exp *exp_data)
{
	if (comp(main->token->cont, '"', '\'', 0) && comp(main->token->cont, '"', '$', 0))
	{
		exp_data->in_quotes = true;
		while (comp(main->token->cont, '"', '\'', 0) || exp_data->in_quotes == true)
		{
			exp_data->i = ft_strlen_def(main->token->cont, '$');
			if (main->token->cont[exp_data->i] == '\0')
				return (false);
			if (comp(main->token->cont + exp_data->i + 1, '$', '"', 1))
			{
				exp_data->i = skip_char(main->token->cont, '"') + 1;
				exp_data->in_quotes = false;
			}
			else
				exp_data->i += skip_char(main->token->cont + exp_data->i, '$');
			tmp_join(exp_data, main);
		}
		return (true);
	}
	return (false);
}

static bool	dollar_expand(t_main *main, t_exp *exp_data)
{
	if (ft_strchr(main->token->cont, '$'))
	{
		while (comp(main->token->cont, '$', '\'', 0) \
			&& comp(main->token->cont, '$', '"', 0))
		{
			exp_data->i = ft_strlen_def(main->token->cont, '$');
			if (comp(main->token->cont, '$', '\'', 0) \
				&& comp(main->token->cont, '$', '"', 0))
			{
				if (comp(main->token->cont + exp_data->i + 1, '$', '"', 1))
					exp_data->i = skip_char(main->token->cont, '"');
				else if (comp(main->token->cont + exp_data->i + 1, '$', '\'', 1))
					exp_data->i = skip_char(main->token->cont, '\'');
				else
					exp_data->i += skip_char(main->token->cont + exp_data->i, '$');
			}
			tmp_join(exp_data, main);
		}
		return (true);
	}
	return (false);
}

void	token_expand(t_main *main)
{
	t_exp	*exp_data;
	t_token	*tmp_token;

	exp_data = NULL;
	tmp_token = main->token;
	exp_data = exp_init(exp_data);
	while (main->token)
	{
		exp_data->in_quotes = false;
		if (single_quote(main->token, exp_data))
			continue ;
		if (double_quote(main, exp_data))
			continue ;
		if (dollar_expand(main, exp_data))
			continue ;
		main->token->cont = end_expand(main->token, exp_data);
		main->token->cont = remove_quote_unsp(main->token->cont);
		main->token = main->token->next;
	}
	main->token = tmp_token;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expansion.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jovieira <jovieira@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/24 12:28:07 by jovieira      #+#    #+#                 */
/*   Updated: 2024/08/16 15:41:30 by jovieira      ########   odam.nl         */
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
static bool	double_quote(t_shell *shell, t_exp *exp_data)
{
	if (comp(shell->token->cont, '"', '\'', 0) && comp(shell->token->cont, '"', '$', 0))
	{
		exp_data->in_quotes = true;
		while (comp(shell->token->cont, '"', '\'', 0) || exp_data->in_quotes == true)
		{
			exp_data->i = ft_strlen_def(shell->token->cont, '$');
			if (shell->token->cont[exp_data->i] == '\0')
				return (false);
			if (comp(shell->token->cont + exp_data->i + 1, '$', '"', 1))
			{
				exp_data->i = skip_char(shell->token->cont, '"') + 1;
				exp_data->in_quotes = false;
			}
			else
				exp_data->i += skip_char(shell->token->cont + exp_data->i, '$');
			tmp_join(exp_data, shell);
		}
		return (true);
	}
	return (false);
}

static bool	dollar_expand(t_shell *shell, t_exp *exp_data)
{
	if (ft_strchr(shell->token->cont, '$'))
	{
		while (comp(shell->token->cont, '$', '\'', 0) \
			&& comp(shell->token->cont, '$', '"', 0))
		{
			exp_data->i = ft_strlen_def(shell->token->cont, '$');
			if (comp(shell->token->cont, '$', '\'', 0) \
				&& comp(shell->token->cont, '$', '"', 0))
			{
				if (comp(shell->token->cont + exp_data->i + 1, '$', '"', 1))
					exp_data->i = skip_char(shell->token->cont, '"');
				else if (comp(shell->token->cont + exp_data->i + 1, '$', '\'', 1))
					exp_data->i = skip_char(shell->token->cont, '\'');
				else
					exp_data->i += skip_char(shell->token->cont + exp_data->i, '$');
			}
			tmp_join(exp_data, shell);
		}
		return (true);
	}
	return (false);
}

void	token_expand(t_shell *shell)
{
	t_exp	*exp_data;
	t_token	*tmp_token;

	exp_data = NULL;
	tmp_token = shell->token;
	exp_data = exp_init(exp_data);
	while (shell->token)
	{
		exp_data->in_quotes = false;
		if (single_quote(shell->token, exp_data))
			continue ;
		if (double_quote(shell, exp_data))
			continue ;
		if (dollar_expand(shell, exp_data))
			continue ;
		shell->token->cont = end_expand(shell->token, exp_data);
		shell->token->cont = remove_quote_unsp(shell->token->cont);
		shell->token = shell->token->next;
	}
	// need proper free function
	free((exp_data->tmp_str));
	free((exp_data->tmp_exp));
	free(exp_data);
	shell->token = tmp_token;
}

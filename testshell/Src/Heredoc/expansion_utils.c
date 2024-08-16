/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expansion_utils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jovieira <jovieira@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/06 11:01:05 by jovieira      #+#    #+#                 */
/*   Updated: 2024/08/16 15:39:09 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*end_expand(t_token *token, t_exp *exp_data)
{
	char *tmp;

	tmp = token->cont;
	if (ft_strlen(token->cont) == 0)
	{
		token->cont = ft_strdup(exp_data->tmp_str);
		free (exp_data->tmp_str);
		if (exp_data->tmp_exp)
			free (exp_data->tmp_exp);
		exp_data->tmp_str = ft_strdup("");
		exp_data->tmp_exp = ft_strdup("");
	}
	else
	{
		token->cont = ft_strjoin(exp_data->tmp_str, token->cont);
		free(exp_data->tmp_str);
		exp_data->tmp_str = ft_strdup("");
	}
	free(tmp);
	return (token->cont);
}

t_exp	*exp_init(t_exp *exp_data)
{
	exp_data = malloc(sizeof(t_exp));
	exp_data->in_quotes = false;
	exp_data->tmp_str = ft_strdup("");
	exp_data->tmp_exp = ft_strdup("");
	return (exp_data);
}

void	tmp_join(t_exp *exp_data, t_shell *shell)
{
		exp_data->tmp_exp = ft_substr(shell->token->cont, 0, exp_data->i);
		ft_memmove (shell->token->cont, shell->token->cont + exp_data->i, \
		ft_strlen(shell->token->cont));
		exp_data->tmp_exp = expandable(exp_data->tmp_exp, shell);
		exp_data->tmp_str = ft_strjoin(exp_data->tmp_str, \
		exp_data->tmp_exp);
}

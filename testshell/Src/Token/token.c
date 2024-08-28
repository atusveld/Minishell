/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jovieira <jovieira@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/24 13:19:14 by jovieira      #+#    #+#                 */
/*   Updated: 2024/08/22 11:40:22 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/shell.h"

static int	syntax_checker(t_token	*temp)
{
	if (!check_double(temp))
		return (1);
	if (!single_char_check(temp))
		return (1);
	if (!exit_cond_valid(temp))
		return (1);
	return (0);
}

int	asign_token(t_token *token)
{
	while (token)
	{
		if (token->cont[0] == '|' && token->cont[1] == '|')
			token->type = PIPEPIPE;
		else if (token->cont[0] == '|')
			token->type = PIPE;
		else if (token->cont[0] == '>' && token->cont[1] == '>')
			token->type = APPEND;
		else if (token->cont[0] == '>')
			token->type = OUT;
		else if (token->cont[0] == '<' && token->cont[1] == '<')
			token->type = HEREDOC;
		else if (token->cont[0] == '<')
			token->type = IN;
		else
			token->type = DEFAULT;
		token = token->next;
	}
	return (0);
}

int	lexer(t_token	*token)
{
	while (token)
	{
		if (syntax_checker(token) == 1)
			return (1);
		token = token->next;
	}
	return (0);
}

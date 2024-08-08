/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jovieira <jovieira@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/24 13:19:14 by jovieira      #+#    #+#                 */
/*   Updated: 2024/08/07 12:20:17 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/main.h"

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

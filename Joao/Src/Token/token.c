/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jovieira <jovieira@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/24 13:19:14 by jovieira      #+#    #+#                 */
/*   Updated: 2024/03/25 12:24:31 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/token.h"

int	asign_token(t_token *token)
{
	int		i;

	i = 0;
	while (token)
	{
		if (token->content[0] == '|' && token->content[1] == '|')
			token->type = PIPEPIPE;
		else if (token->content[0] == '|')
			token->type = PIPE;
		else if (token->content[0] == '>' && token->content[1] == '>')
			token->type = APPEND;
		else if (token->content[0] == '>')
			token->type = OUT;
		else if (token->content[0] == '<' && token->content[1] == '<')
			token->type = HEREDOC;
		else if (token->content[0] == '<')
			token->type = IN;
		else
			token->type = DEFAULT;
		token = token->next;
	}
	return (0);
}

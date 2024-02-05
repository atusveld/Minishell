/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jovieira <jovieira@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/24 13:19:14 by jovieira      #+#    #+#                 */
/*   Updated: 2024/02/05 15:43:48 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/token.h"

int	asign_token(t_token *token)
{
	int i = 0;
	token->line = *ft_token(token->input);
	// token = malloc(sizeof(ft_strlen(token->input)));
	while (token->line[i])
	{
		token = ft_lstnew(token->line);
		// while (token.token[i])
		
		// if (!token->token)
		// 	ft_lstclear(token->token);
		// ft_lstadd_back(&token->token, &token->token[i]);
		// token->token = token->line[i];
		// token = token->next;
		// printf("<%s>\n", token->token[i]);
		i++;
	}
	return (0);
}

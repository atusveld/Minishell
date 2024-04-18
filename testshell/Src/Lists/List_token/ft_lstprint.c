/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstprint.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jovieira <jovieira@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/28 16:32:37 by jovieira      #+#    #+#                 */
/*   Updated: 2024/04/09 12:46:46 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/token.h"

void	ft_lstprint(t_token *token)
{
	while (token)
	{
		printf("content %s, tipo %i, operador %i, infile red %i\n", \
		token->content, token->type, token->operator, token->infile);
		token = token->next;
	}
}

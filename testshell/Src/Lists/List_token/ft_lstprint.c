/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstprint.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jovieira <jovieira@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/28 16:32:37 by jovieira      #+#    #+#                 */
/*   Updated: 2024/08/06 11:08:39 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/token.h"

void	ft_lstprint(t_token *token)
{
	while (token)
	{
		printf("content %s, tipo %i, operador %i, infile red %i\n", \
		token->cont, token->type, token->operator, token->infile);
		token = token->next;
	}
}

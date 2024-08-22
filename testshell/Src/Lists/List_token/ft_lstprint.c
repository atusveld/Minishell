/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstprint.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jovieira <jovieira@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/28 16:32:37 by jovieira      #+#    #+#                 */
/*   Updated: 2024/08/22 11:37:44 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/shell.h"

void	ft_lstprint(t_token *token)
{
	while (token)
	{
		printf("content %s, tipo %i\n", token->cont, token->type);
		token = token->next;
	}
}

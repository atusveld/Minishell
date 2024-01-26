/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jovieira <jovieira@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/24 13:19:14 by jovieira      #+#    #+#                 */
/*   Updated: 2024/01/26 17:21:42 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/token.h"

int	asign_token(t_token	*token)
{
	int i = 0;
	token->line_history = ft_token(token->line);
	while (token->line_history[i])
	{
		printf("%s\n", token->line_history[i]);
		i++;
	}
	return (0);
}

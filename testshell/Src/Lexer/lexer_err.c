/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_err.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jovieira <jovieira@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/13 13:00:18 by jovieira      #+#    #+#                 */
/*   Updated: 2024/08/06 17:36:44 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/shell.h"

void	lexer_error(int error, char *word)
{
	if (error == 2)
	{
		write(2, NEAR_TOKEN, ft_strlen(NEAR_TOKEN));
		write(2, word, ft_strlen(word));
		write(2, "'\n", 2);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_err.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jovieira <jovieira@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/13 13:00:18 by jovieira      #+#    #+#                 */
/*   Updated: 2024/08/22 11:43:47 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/shell.h"

void	lexer_error(char *word)
{
		write(STDOUT_FILENO, NEAR_TOKEN, ft_strlen(NEAR_TOKEN));
		write(STDOUT_FILENO, word, ft_strlen(word));
		write(STDOUT_FILENO, "'\n", 2);
}

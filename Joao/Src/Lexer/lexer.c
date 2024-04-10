/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jovieira <jovieira@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/26 17:39:29 by jovieira      #+#    #+#                 */
/*   Updated: 2024/04/09 12:37:09 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	syntax_checker(t_token	*temp)
{
	valid_operator(temp);
	redirect_check(temp);
	if (!check_double(temp))
		return (1);
	if (!single_char_check(temp))
		return (1);
	if (!exit_cond_valid(temp))
		return (1);
	return (0);
}

int	lexer(t_token	*token)
{
	if (syntax_checker(token) == 1)
		return (1);
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jovieira <jovieira@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/24 13:16:59 by jovieira      #+#    #+#                 */
/*   Updated: 2024/04/09 11:59:24 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "token.h"

# define NEAR_TOKEN "minishell: syntax error near unexpected token `"

// Lexer Main Function
int		lexer(t_token	*token);

// Error assign Function
void	lexer_error(int error, char *word);

// Extra Node Info Functions
void	valid_operator(t_token *temp);
void	redirect_check(t_token *temp);

// Syntax check Functions
bool	check_double(t_token *temp);
bool	exit_cond_valid(t_token *temp);
bool	single_char_check(t_token *temp);

#endif
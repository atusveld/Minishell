/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jovieira <jovieira@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/24 13:16:59 by jovieira      #+#    #+#                 */
/*   Updated: 2024/04/03 10:56:48 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "token.h"

# define NEAR_TOKEN "minishell: syntax error near unexpected token `"

int		lexer(t_token	*token);
bool		single_char_check(t_token *temp);
bool		check_double(t_token *temp);
bool	exit_cond_valid(t_token *temp);
void	valid_operator(t_token *token);
void	lexer_error(int error, char *word);
void	valid_operator(t_token *temp);
void	redirect_check(t_token *temp);

#endif
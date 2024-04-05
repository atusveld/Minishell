/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jovieira <jovieira@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/24 13:16:56 by jovieira      #+#    #+#                 */
/*   Updated: 2024/04/03 14:22:56 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "lexer.h"

typedef	struct s_red
{
	int				fd; // return from function open, after close file
	char			*filename; // </>/<< + arg // <<???
	t_type			type;
	struct s_red	*next;
}			t_red;

typedef struct s_parse
{
	char			**argv;
	t_red			*redir_in;
	t_red			*redir_out;
	struct s_parse	*next;
}	t_parse;



int	parse(t_token *token);

#endif
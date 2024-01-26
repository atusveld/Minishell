/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jovieira <jovieira@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/24 13:15:46 by jovieira      #+#    #+#                 */
/*   Updated: 2024/01/26 14:34:53 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "../Libft/libft.h"
# include <stdlib.h>
# include <stdio.h>

typedef struct s_token
{
	char	*line;
	char	**line_history;
}	t_token;

#endif

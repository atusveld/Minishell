/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jovieira <jovieira@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/24 13:15:46 by jovieira      #+#    #+#                 */
/*   Updated: 2024/01/24 15:50:25 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "../Libft/libft.h"
# include <stdlib.h>

typedef struct	t_token
{
	char	*line;
	char	**pre_token;
}				t_token;


#endif

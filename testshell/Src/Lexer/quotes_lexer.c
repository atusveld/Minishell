/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quotes_lexer.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jovieira <jovieira@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/22 11:47:58 by jovieira      #+#    #+#                 */
/*   Updated: 2024/08/06 17:36:44 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/shell.h"

static bool	check_closed_quotes(char *token)
{
	size_t	i;
	char	*c;

	i = 0;
	while (*(token + i) != '\0')
	{
		if (*(token + i) == '\'' || *(token + i) == '"')
		{
			c = ft_substr(token, i, 1);
			i = skip_quotes(token, i);
		}
		if (*(token + i) == '\0')
		{
			lexer_error(2, c);
			free(c);
			return (false);
		}
		i++;
	}
	return (true);
}

bool	exit_cond_valid(t_token *temp)
{
	if (temp && temp->type == DEFAULT)
		return (check_closed_quotes(temp->cont));
	return (true);
}

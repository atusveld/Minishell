/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   syntax.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jovieira <jovieira@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/26 17:40:51 by jovieira      #+#    #+#                 */
/*   Updated: 2024/08/22 11:44:14 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/shell.h"

// void	valid_operator(t_token *temp)
// {
// 	while (temp)
// 	{
// 		temp->operator = 0;
// 		if (temp->next && (temp->type >= PIPE && temp->type <= HEREDOC) && \
// 		temp->next->type == DEFAULT)
// 			temp->operator = 1;
// 		temp = temp->next;
// 	}
// }

// void	redirect_check(t_token *temp)
// {
// 	while (temp)
// 	{
// 		temp->infile = 0;
// 		if (temp->type == DEFAULT)
// 			if (temp->next && temp->next->next && \
// 			(temp->next->type >= IN && temp->next->type <= APPEND))
// 				if (temp->next->next->type == DEFAULT)
// 					temp->infile = 1;
// 		temp = temp->next;
// 	}
// }

static bool	check_closed_quotes(char *token)
{
	size_t	i;
	char	*c;

	c = ft_strdup("");
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
			lexer_error(c);
			free(c);
			return (false);
		}
		i++;
	}
	if (c)
		free(c);
	return (true);
}

bool	exit_cond_valid(t_token *temp)
{
	if (temp && temp->type == DEFAULT)
		return (check_closed_quotes(temp->cont));
	return (true);
}

bool	single_char_check(t_token *temp)
{
	while (temp)
	{
		if (!temp->next && (temp->type >= PIPEPIPE && temp->type <= HEREDOC))
		{
			lexer_error(temp->cont);
			return (false);
		}
		temp = temp->next;
	}
	return (true);
}

bool	check_double(t_token *temp)
{
	while (temp)
	{
		if ((temp->cont[0] == '&' && temp->cont[1] == '&') || \
		(temp->cont[0] == '$' && temp->cont[1] == '$'))
		{
			lexer_error(temp->cont);
			return (false);
		}
		temp = temp->next;
	}
	return (true);
}

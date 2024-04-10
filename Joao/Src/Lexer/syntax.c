/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   syntax.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jovieira <jovieira@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/26 17:40:51 by jovieira      #+#    #+#                 */
/*   Updated: 2024/04/01 16:26:18 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	valid_operator(t_token *temp)
{
	while (temp)
	{
		temp->operator = 0;
		if (temp->next && (temp->type >= PIPE && temp->type <= HEREDOC) && \
		temp->next->type == DEFAULT)
			temp->operator = 1;
		temp = temp->next;
	}
}

void	redirect_check(t_token *temp)
{
	while (temp)
	{
		temp->infile = 0;
		if (temp->type == DEFAULT)
			if (temp->next && temp->next->next && \
			(temp->next->type >= IN && temp->next->type <= APPEND))
				if (temp->next->next->type == DEFAULT)
					temp->infile = 1;
		temp = temp->next;
	}
}

bool	single_char_check(t_token *temp)
{
	while (temp)
	{
		if (!temp->next && (temp->type >= PIPEPIPE && temp->type <= HEREDOC))
		{
			lexer_error(2, temp->content);
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
		if ((temp->content[0] == '&' && temp->content[1] == '&') || \
		(temp->content[0] == '$' && temp->content[1] == '$'))
		{
			lexer_error(2, temp->content);
			return (false);
		}
		temp = temp->next;
	}
	return (true);
}

// int	parent_check(t_token *temp)
// {
// 	while (temp)
// 	{
// 		if (ft_strchr(temp->content, '('))
// 		{
// 			if (!ft_strchr(temp->content, ')') && temp->next)
// 				temp = temp->next;
// 			else
// 			{
// 				lexer_error(2, ")");
// 				return (1);
// 			}
// 		}
// 		temp = temp->next;
// 	}
// 	return (0);
// }

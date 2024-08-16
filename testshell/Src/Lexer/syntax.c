/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   syntax.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jovieira <jovieira@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/26 17:40:51 by jovieira      #+#    #+#                 */
/*   Updated: 2024/08/06 17:36:44 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/shell.h"

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
			lexer_error(2, temp->cont);
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
			lexer_error(2, temp->cont);
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
// 		if (ft_strchr(head->cont, '('))
// 		{
// 			if (!ft_strchr(head->cont, ')') && temp->next)
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

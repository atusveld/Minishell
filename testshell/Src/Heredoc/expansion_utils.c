/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expansion_utils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jovieira <jovieira@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/24 12:28:07 by jovieira      #+#    #+#                 */
/*   Updated: 2024/07/09 13:17:54 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

// void	quote_check(char *str)
// {
// 	int		i;
// 	char	c;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '\'')
// 		{
			
			
// 		}
// 		i++;
// 	}
// }



void	token_expand(t_token *token, t_env *tmp_env)
{
	int	i;
	bool	db_quotes;
	// bool	here;

	i = 0;
	while (token)
	{
		db_quotes = true;
		if (token->type == HEREDOC)
			token->next->operator = 1;
		if (ft_strchr(token->content, '\''))
		{
			printf("here '\n");
			token->content = remove_quote(token->content, '\'');
			db_quotes = false;
		}
		printf("token->content = %s\n", token->content);
		if (ft_strchr(token->content, '"') /*&& token->next->operator == 1*/)
		{
			printf("here \"\n");
			token->content = remove_quote(token->content, '"');
			db_quotes = true;
		}
		if (ft_strchr(token->content, '$') && db_quotes == true)
		{
			printf("here $\n");
			token->content = expandable(token->content, tmp_env);
			continue;
		}
		// if (db_quotes == false)
		// 	return ;
		token = token->next;
	}
	// return ()
}

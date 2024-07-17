/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expansion_utils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jovieira <jovieira@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/24 12:28:07 by jovieira      #+#    #+#                 */
/*   Updated: 2024/07/14 15:42:02 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"


static size_t	skip_quotes(char *line)
{
	int i;

	i = 0;
	while (*(line + i) != '\'' && *(line + i) != '"' && *(line + i) != '\0')
		i++;
	printf("%c\n", line[i]);
	return (i);
}

// void	token_expand(t_token *token, t_env *tmp_env)
// {
// 	int	i;

// 	i = 0;
// 	while (token)
// 	{
// 		if (token->content[i] == '\'')
// 		{
// 			// printf("%c\n", token->content[i]);
// 			i = skip_quotes(token->content, i);
// 			// i++;
// 			// printf("%i\n", i);
			
// 		}
// 		// printf("%c\n", token->content[i]);
// 		if (token->content[i + 1] == '"')
// 		{	
// 			token->content  = remove_quote(token->content, '"');
// 			i++;
// 		}
// 		// printf("%i, %c\n", i, token->content[i]);
// 		if (token->content[i] == '$')
// 		{
// 			token->content = expandable(token->content, tmp_env);
// 		}
// 		token = token->next;
// 	}
// }

void	token_expand(t_token *token, t_env *tmp_env)
{
	int i;
	bool	db_quotes;
	// bool	here;

	// while (str[i]) {
	// 	if ('\'') {
	// 		i+++++++++ second;
	// 	}
	// 	if (str[i] == '$')
	// 	{}
	// 	i++;
	// }

	while (token)
	{
		db_quotes = true;
		if (token->type == HEREDOC)
			token->next->operator = 1;
		i = skip_quotes(token->content);
		if (token->content[i] == '\'')
		{
			// printf("here '\n");
			token->content = remove_quote(token->content, '\'');
			db_quotes = false;
		}
		else if (token->content[i] == '"')
		{
			// printf("here \"\n");
			// i = ft_strchr(token->content, '"') - token->content;
			token->content = remove_quote(token->content, '"');
			db_quotes = true;
		}
		printf("%i\n", db_quotes);
		if (db_quotes == true)
		{
			// printf("here $\n");
			token->content = expandable(token->content, tmp_env);
			continue;
		}
		// if (db_quotes == false)
		// 	return ;
		token = token->next;
	}
	// return ()
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expansion_utils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jovieira <jovieira@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/24 12:28:07 by jovieira      #+#    #+#                 */
/*   Updated: 2024/07/22 15:07:05 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"


static size_t	skip_quotes(char *line)
{
	int i;

	i = 1;
	while (line[i] != '\'' && line[i] != '"' && line[i] != '\0')
		i++;
	return (i);
}

void	token_expand(t_token *token, t_env *tmp_env)
{
	int 	i;
	bool	db_quotes;
	char	*tmp_str;
	char	*tmp_exp;

	// (void)tmp_env;
	tmp_str = ft_strdup("");
	while (token)
	{
		db_quotes = true;
		i = skip_quotes(token->content);
		if (token->content[i] == '\'')
		{
			tmp_str = ft_strjoin(tmp_str, ft_substr(token->content, 0, i + 1));
			// printf("tmp_str: %s i: %i\n", tmp_str, i);
			ft_memmove (token->content, token->content + i + 1, ft_strlen(token->content));
			// printf("token->content: %s\n", token->content);
			db_quotes = false;
			// continue;
		}
		// }
		if (ft_strchr(token->content, '$') && db_quotes == true)
		{
			printf("token->content: %s\n", token->content);
			i = ft_strlen_def(token->content, '"');
			printf("i: %i\n", i);
			if (token->content[i] == '"')
				tmp_exp = ft_substr(token->content, 0, i + 1);
			else
				tmp_exp = ft_substr(token->content, 0, i);
			ft_memmove (token->content, 0, i + 1);
			printf("token->content: %s\n", token->content);
			tmp_exp = expandable(tmp_exp, tmp_env);
			printf("tmp_exp: %s\n", tmp_exp);
			tmp_str = ft_strjoin(tmp_str, tmp_exp);
			printf("tmp_str: %s\n", tmp_str);
			// if (ft_strlen(token->content) != 0)
			// tmp_exp = ft_substr(token->content, 0, i + 1);
			// ft_memmove (token->content, token->content + i + 1, ft_strlen(token->content));
			// tmp_exp = expandable(tmp_exp, tmp_env);
			// tmp_exp = remove_quote(tmp_exp, '"');
			// tmp_str = ft_strjoin(tmp_str, tmp_exp);
			db_quotes = true;
			// token->content = ft_strdup(tmp_str);
			// continue;
		}
		// if(ft_strlen(token->content) == 0)
		// {
		// 	printf("tmp_str no fim do loop: %s\n", tmp_str);
		// 	tmp_str = remove_quote(tmp_str, '\'');
		// 	token->content = ft_strdup(tmp_str);
		// 	break;
		// }
		// printf("token->content: %s\n", token->content);
		token = token->next;
		// token = token->next;
	}
	// return ()
}

			// printf("token: [%s]\n", token->content);
			// printf("tmp_str: %s\n", tmp_str);
		// printf("%c\n", token->content[i]);
// echo '$USER'"$USER"$USER
// echo "$USER"$USER'$USER'
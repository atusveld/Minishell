/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expansion_utils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jovieira <jovieira@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/24 12:28:07 by jovieira      #+#    #+#                 */
/*   Updated: 2024/07/25 15:38:53 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"


static size_t	skip_char(char *line, char c)
{
	int i;

	i = 1;
	while (line[i] != c && line[i] != '\0')
		i++;
	return (i);
}

static size_t	skip_quotes(char *token, size_t i)
{
	char	c;

	c = *(token + i);
	i++;
	while (*(token + i) != c && *(token + i) != '\0')
		i++;
	return (i);
}

void	token_expand(t_token *token, t_env *tmp_env) // double or no quotes is copying one character too many from single quotes
{
	int 	i;
	bool	db_quotes;
	bool	in_quotes;
	char	*tmp_str;
	char	*tmp_exp;

	(void)tmp_env;
	tmp_str = ft_strdup("");
	while (token)
	{
		db_quotes = true;
		in_quotes = false;
		if (ft_strlen_def(token->content, '\'') < ft_strlen_def(token->content, '"') && ft_strlen_def(token->content, '\'') < ft_strlen_def(token->content, '$'))
		{
			i = ft_strlen_def(token->content, '\'');
			i = skip_quotes(token->content, i);
			tmp_str = ft_strjoin(tmp_str, ft_substr(token->content, 0, i + 1));
			ft_memmove (token->content, token->content + i + 1, ft_strlen(token->content));
			db_quotes = false;
			continue;
		}
		if (ft_strlen_def(token->content, '"') < ft_strlen_def(token->content, '\'') && ft_strlen_def(token->content, '"') < ft_strlen_def(token->content, '$'))
		{
			while (ft_strlen_def(token->content, '\'') > ft_strlen_def(token->content, '"') && ft_strlen_def(token->content, '\'') > ft_strlen_def(token->content, '$'))
			{
				i = ft_strlen_def(token->content, '$');
				printf("i: %i\n", i);
				if (ft_strlen_def(tmp_exp, '$') > ft_strlen_def(tmp_exp, '"') || in_quotes == true)
				{
					i = skip_char(token->content, '"');
					printf("in \" i: %i\n", i);
				}
				else
				{
					i = skip_char(token->content + i, '$');
					printf("in \" $ i: %i\n", i);
				}
				tmp_exp = ft_substr(token->content, 0, i + 1);
				ft_memmove (token->content, token->content + i + 1, ft_strlen(token->content));
				tmp_exp = expandable(tmp_exp, tmp_env);
				tmp_str = ft_strjoin(tmp_str, tmp_exp);
				in_quotes = true;
			}
		}
		if (ft_strchr(token->content, '$') && db_quotes == true)
		{
			while (ft_strlen_def(token->content, '$') < ft_strlen_def(token->content, '\'') && ft_strlen_def(token->content, '$') < ft_strlen_def(token->content, '"'))
			{
			printf("token->content: %s\n", token->content);
			i = ft_strlen_def(token->content, '$');
			printf("i: %i\n", i);
			i = skip_char(token->content + i, '$');
			printf("in no quote i: %i\n", i);
			tmp_exp = ft_substr(token->content, 0, i);
			printf("tmp_exp: %s\n", tmp_exp);
			tmp_exp = expandable(tmp_exp, tmp_env);
			ft_memmove (token->content, token->content + i, ft_strlen(token->content));
			printf("tmp_exp: %s\n", tmp_exp);
			tmp_str = ft_strjoin(tmp_str, tmp_exp);
			printf("tmp_str: %s\n", tmp_str);
			}
			db_quotes = true;
			continue;
		}
		if (ft_strlen(token->content) == 0)
			token->content = tmp_str;
		token = token->next;
	}
	// return ()
}

			// printf("token: [%s]\n", token->content);
			// printf("tmp_str: %s\n", tmp_str);
		// printf("%c\n", token->content[i]);
// echo '$USER'"$USER"$USER
// echo "$USER"$USER'$USER'
/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expansion_utils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jovieira <jovieira@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/24 12:28:07 by jovieira      #+#    #+#                 */
/*   Updated: 2024/07/18 18:17:40 by jovieira      ########   odam.nl         */
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

	(void)tmp_env;
	tmp_str = ft_strdup("");
	while (token)
	{
		db_quotes = true;
		i = skip_quotes(token->content);
		printf("%c\n", token->content[i]);
		if (token->content[i] == '\'')
		{
			tmp_str = ft_substr(token->content, 0, i + 1);
			ft_memmove (token->content, token->content + i + 1, ft_strlen(token->content));
			db_quotes = false;
		}
		if (ft_strchr(token->content, '"'))
		{
			i = ft_strlen_def(token->content, '"');
			tmp_exp = ft_substr(token->content, 0, i + 1);
			ft_memmove (token->content, token->content + i + 1, ft_strlen(token->content));
			tmp_exp = expandable(tmp_exp, tmp_env);
			tmp_exp = remove_quote(tmp_exp, '"');
			tmp_str = ft_strjoin(tmp_str, tmp_exp);
			db_quotes = true;
		}
		if (db_quotes == true && ft_strchr(token->content, '$'))
		{
			tmp_exp = expandable(token->content, tmp_env);
			tmp_str = ft_strjoin(tmp_str, tmp_exp);
			if (ft_strlen(token->content) != 0)
				ft_memmove (token->content, token->content + i + 1, ft_strlen(token->content));
			printf("token: [%s]\n", token->content);
			printf("tmp_str: %s\n", tmp_str);
			// token->content = ft_strdup(tmp_str);
			continue;
		}
		if(ft_strlen(token->content) == 0)
		{
			tmp_str = remove_quote(tmp_str, '\'');
			token->content = ft_strdup(tmp_str);
			break;
		}
		token = token->next;
	}
	// return ()
}

// echo '$USER'"$USER"$USER
// echo "$USER"$USER'$USER'
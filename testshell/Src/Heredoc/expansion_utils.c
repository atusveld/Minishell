/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expansion_utils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jovieira <jovieira@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/24 12:28:07 by jovieira      #+#    #+#                 */
/*   Updated: 2024/07/31 19:02:10 by jovieira      ########   odam.nl         */
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

bool	single_quote(t_token *token, t_exp *expand_data)
{
	printf("token->content: %s\n", token->content);
	if (ft_strlen_def(token->content, '\'') < ft_strlen_def(token->content, '"') && ft_strlen_def(token->content, '\'') < ft_strlen_def(token->content, '$'))
	{
		expand_data->i = ft_strlen_def(token->content, '\'');
		expand_data->i = skip_quotes(token->content, expand_data->i);
		expand_data->tmp_str = ft_strjoin(expand_data->tmp_str, ft_substr(token->content, 0, expand_data->i + 1));
		printf("tmp_str: %s\n", expand_data->tmp_str);
		ft_memmove (token->content, token->content + expand_data->i + 1, ft_strlen(token->content));
		return (true);
	}
	return (false);
}
// +1 in skip_char " to include the quote
bool	double_quote(t_token *token, t_exp	*expand_data, t_env *tmp_env)
{
	if (ft_strlen_def(token->content, '"') < ft_strlen_def(token->content, '\'') && ft_strlen_def(token->content, '"') < ft_strlen_def(token->content, '$'))
	{
		expand_data->in_quotes = true;
		while (ft_strlen_def(token->content, '"') < ft_strlen_def(token->content, '\'') || expand_data->in_quotes == true)
		{
			expand_data->i = ft_strlen_def(token->content, '$');
			if (token->content[expand_data->i] == '\0')
				break ;
			if (ft_strlen_def(token->content + expand_data->i + 1, '$') > ft_strlen_def(token->content + expand_data->i + 1, '"'))
			{
				expand_data->i = skip_char(token->content, '"') + 1; 
					expand_data->in_quotes = false;
			}
			else
				expand_data->i += skip_char(token->content + expand_data->i, '$');
			expand_data->tmp_exp = ft_substr(token->content, 0, expand_data->i);
			ft_memmove (token->content, token->content + expand_data->i, ft_strlen(token->content));
			printf("tmp_exp: %s\n", expand_data->tmp_exp);
			expand_data->tmp_exp = expandable(expand_data->tmp_exp, tmp_env);
			expand_data->tmp_str = ft_strjoin(expand_data->tmp_str, expand_data->tmp_exp);
		}
		return (true);
	}
	return (false);
}

bool	dollar_expand(t_token *token, t_exp *expand_data, t_env *tmp_env)
{
	if (ft_strchr(token->content, '$'))
	{
		while (ft_strlen_def(token->content, '$') < ft_strlen_def(token->content, '\'') && ft_strlen_def(token->content, '$') < ft_strlen_def(token->content, '"'))
		{
			expand_data->i = ft_strlen_def(token->content, '$');
			if (ft_strlen_def(token->content, '$') < ft_strlen_def(token->content, '\'') && ft_strlen_def(token->content, '$') < ft_strlen_def(token->content, '"'))
			{
				if (ft_strlen_def(token->content + expand_data->i + 1, '$') > ft_strlen_def(token->content + expand_data->i + 1, '"'))
					expand_data->i = skip_char(token->content, '"');
				else if (ft_strlen_def(token->content + expand_data->i + 1, '$') > ft_strlen_def(token->content + expand_data->i + 1, '\''))
					expand_data->i = skip_char(token->content, '\'');
				else
					expand_data->i += skip_char(token->content + expand_data->i, '$');
			}
			expand_data->tmp_exp = ft_substr(token->content, 0, expand_data->i);
			expand_data->tmp_exp = expandable(expand_data->tmp_exp, tmp_env);
			ft_memmove (token->content, token->content + expand_data->i, ft_strlen(token->content));
			expand_data->tmp_str = ft_strjoin(expand_data->tmp_str, expand_data->tmp_exp);
		}
		return (true);
	}
	return (false);
}

void	token_expand(t_token *token, t_env *tmp_env)
{
	t_exp	*expand_data;

	expand_data = malloc(sizeof(t_exp));
	(void)tmp_env;
	expand_data->tmp_str = ft_strdup("");
	expand_data->tmp_exp = ft_strdup("");
	while (token)
	{
		expand_data->in_quotes = false;
		if (single_quote(token, expand_data))
			continue;
		if (double_quote(token, expand_data, tmp_env))
			continue;
		if (dollar_expand(token, expand_data, tmp_env))
			continue;
		if (ft_strlen(token->content) == 0)
		{
			token->content = ft_strdup(expand_data->tmp_str);
			free (expand_data->tmp_str);
			if (expand_data->tmp_exp)
				free (expand_data->tmp_exp);
			free(expand_data);
		}
		token = token->next;
	}
}

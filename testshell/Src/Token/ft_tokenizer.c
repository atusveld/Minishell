/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_tokenizer.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jovieira <jovieira@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/24 15:57:14 by jovieira      #+#    #+#                 */
/*   Updated: 2024/08/06 17:36:44 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/main.h"
// #include "../Includes/main.h"

static void	meta_char(char *meta_character[5])
{
	meta_character[0] = "|";
	meta_character[1] = "<<";
	meta_character[2] = ">>";
	meta_character[3] = ">";
	meta_character[4] = "<";
}

static char	*is_meta_char(char *s, char *meta_character[6])
{
	int	i;

	i = 0;
	while (i < 5)
	{
		if (ft_strncmp(s, meta_character[i], ft_strlen(meta_character[i])) == 0)
			return (meta_character[i]);
		i++;
	}
	return (NULL);
}

static bool	white_space_check(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (!ft_isspace(s[i]))
			return (false);
		(i)++;
	}
	return (true);
}

static void	check_quotes(char *s, int *i)
{
	char	*c;

	if (s[*i] == '\"' || s[*i] == '\'')
	{
		c = &s[*i];
		(*i)++;
		while (s[*i] != *c)
		{
			if (!s[*i])
				return ;
			(*i)++;
		}
		(*i)++;
		return ;
	}
	(*i)++;
	return ;
}

t_token	*ft_token(char *s)
{
	t_token	*token;
	char	*meta_character[5];
	int		i;

	meta_char(meta_character);
	token = NULL;
	if (s == NULL || white_space_check(s) == true)
		return (NULL);
	while (*s)
	{
		i = 0;
		while (*s == ' ' && *s != '\0' && *s != '"' && *s != '\'')
			s++;
		if (is_meta_char(&s[i], meta_character))
			i = ft_strlen(is_meta_char(&s[i], meta_character));
		else
			while (s[i] != ' ' && s[i] && !is_meta_char(&s[i], meta_character))
				check_quotes(s, &i);
		ft_lstadd_back(&token, ft_lstnew(ft_substr(s, 0, i)));
		s += i;
	}
	return (token);
}

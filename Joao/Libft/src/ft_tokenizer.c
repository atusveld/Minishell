/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_tokenizer.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jovieira <jovieira@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/24 15:57:14 by jovieira      #+#    #+#                 */
/*   Updated: 2024/02/02 16:20:20 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static bool	check_quotes(char *s, int *i)
{
	if (s[*i] == '"')
	{
		(*i)++;
		while (s[*i] != '"')
		{
			if (!s[*i])
				break ;
			(*i)++;
		}
		(*i)++;
		return (true);
	}
	return (false);
}

static int	str_count(char *s)
{
	size_t	str_c;
	int		i;

	i = 0;
	str_c = 0;
	while (s[i])
	{
		while (s[i] == ' ')
			i++;
		if (s[i] != '\0')
			str_c++;
		while (s[i] != ' ' && s[i])
			if (!check_quotes(s, &i))
				i++;
	}
	return (str_c);
}

static void	free_mem(char **string, int j)
{
	while (j >= 0)
	{
		free(string[j]);
		j--;
	}
	free(string);
}

char	**ft_token(char *s)
{
	char	**string;
	int		str_cnt;
	int		i;
	int		j;

	j = 0;
	str_cnt = str_count(s);
	string = malloc((str_cnt + 1) * sizeof (char *));
	if (string == NULL)
		return (NULL);
	while (j < str_cnt)
	{
		i = 0;
		while (*s == ' ' && *s != '\0' && *s != '"')
			s++;
		while (s[i] != ' ' && s[i])
			if (!check_quotes(s, &i))
				i++;
		string[j] = ft_substr(s, 0, i);
		if (string[j] == NULL)
			return (free_mem(string, j), NULL);
		s += i;
		j++;
	}
	string[j] = NULL;
	return (string);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_tokenizer.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jovieira <jovieira@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/24 15:57:14 by jovieira      #+#    #+#                 */
/*   Updated: 2024/01/26 14:36:15 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	dictionary(void)
{
	
}

static int	str_count(char const *s)
{
	size_t	str_c;

	str_c = 0;
	while (*s)
	{
		while ((*s == '|' || *s == '<' || *s == '>' || *s == "<<" || *s == ">>") && *s)
			s++;
		if (*s != '\0')
			str_c++;
		while (*s != c && *s)
			s++;
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

char	**ft_token(char const *s)
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
		while (*s == c && *s != '\0')
			s++;
		while (s[i] != c && s[i] != '\0')
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

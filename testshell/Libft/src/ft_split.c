/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jovieira <jovieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 15:10:46 by jovieira          #+#    #+#             */
/*   Updated: 2022/10/31 22:42:44 by jovieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	str_count(char const *s, char c)
{
	size_t	str_c;

	str_c = 0;
	while (*s)
	{
		while (*s == c && *s)
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

static char	**getmem(char const *s, char c)
{
	char	**string;
	int		str_cnt;
	int		i;
	int		j;

	j = 0;
	str_cnt = str_count(s, c);
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

char	**ft_split(char const *s, char c)
{
	char	**f;

	if (!s)
		return (NULL);
	f = getmem(s, c);
	return (f);
}

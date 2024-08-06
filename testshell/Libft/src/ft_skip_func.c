/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_skip_func.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jovieira <jovieira@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/31 19:06:32 by jovieira      #+#    #+#                 */
/*   Updated: 2024/07/31 19:12:49 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	skip_char(char *line, char c)
{
	int i;

	i = 1;
	while (line[i] != c && line[i] != '\0')
		i++;
	return (i);
}

size_t	skip_quotes(char *line, size_t i)
{
	char	c;

	c = *(line + i);
	i++;
	while (*(line + i) != c && *(line + i) != '\0')
		i++;
	return (i);
}

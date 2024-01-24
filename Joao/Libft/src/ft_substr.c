/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jovieira <jovieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 19:02:08 by jovieira          #+#    #+#             */
/*   Updated: 2022/11/02 15:12:12 by jovieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (s_len <= start)
		return (ft_strdup(""));
	s_len = ft_strlen(&s[start]);
	if (s_len < len)
		len = s_len;
	str = malloc((len + 1) * sizeof (char));
	if (str == NULL)
		return (NULL);
	ft_memcpy(str, &s[start], len);
	str[len] = '\0';
	return (str);
}

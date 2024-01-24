/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jovieira <jovieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 18:03:38 by jovieira          #+#    #+#             */
/*   Updated: 2022/11/02 21:03:43 by jovieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	len_dst;
	size_t	len_src;
	size_t	new_len;
	size_t	i;
	char	*s;

	if (dstsize == 0)
		return (ft_strlen(src));
	len_src = ft_strlen(src);
	len_dst = ft_strlen(dst);
	new_len = len_src + dstsize;
	i = 0;
	s = (char *)src;
	if (dstsize > len_dst)
		new_len = len_src + len_dst;
	while (s[i] && (len_dst + 1) < dstsize)
	{
		dst[len_dst] = src[i];
		len_dst++;
		i++;
	}
	dst[len_dst] = '\0';
	return (new_len);
}

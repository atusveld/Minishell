/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jovieira <jovieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 15:41:00 by jovieira          #+#    #+#             */
/*   Updated: 2022/11/02 21:00:03 by jovieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;
	char	*d;
	char	*s;

	i = 0;
	d = (char *)dst;
	s = (char *)src;
	if (dst == NULL && src == NULL)
		return (NULL);
	if (d > s)
	{
		while (len-- > 0)
				d[len] = s[len];
	}			
	else
	{
		while (i < len)
		{
			d[i] = s[i];
			i++;
		}
	}	
	return (dst);
}

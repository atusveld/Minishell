/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstclear_bonus.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: jovieira <jovieira@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/30 15:30:48 by jovieira      #+#    #+#                 */
/*   Updated: 2024/02/05 14:57:18 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/token.h"

void	ft_lstclear(t_token **lst, void (*del)(void*))
{
	t_token	*temp;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = temp;
	}
}

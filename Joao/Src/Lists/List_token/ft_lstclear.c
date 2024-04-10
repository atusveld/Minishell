/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstclear.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jovieira <jovieira@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/30 15:30:48 by jovieira      #+#    #+#                 */
/*   Updated: 2024/04/09 12:46:31 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/token.h"

// void	ft_lstclear(t_token **lst, void (*del)(void*))
// {
// 	t_token	*temp;

// 	if (!lst || !del)
// 		return ;
// 	while (*lst)
// 	{
// 		temp = (*lst)->next;
// 		ft_lstdelone(*lst, del);
// 		*lst = temp;
// 	}
// }

void	ft_lstclear_mod(t_token **lst)
{
	t_token	*temp;

	if (!lst)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		ft_lstdelone_mod(*lst);
		*lst = temp;
	}
}

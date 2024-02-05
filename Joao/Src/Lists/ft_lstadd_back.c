/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstadd_back_bonus.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jovieira <jovieira@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/27 21:34:46 by jovieira      #+#    #+#                 */
/*   Updated: 2024/02/05 15:01:59 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/token.h"

void	ft_lstadd_back(t_token **lst, t_token *new)
{
	t_token	*tail;

	if (!lst)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	tail = ft_lstlast(*lst);
	tail->next = new;
}

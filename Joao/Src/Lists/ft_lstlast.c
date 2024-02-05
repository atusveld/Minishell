/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstlast_bonus.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: jovieira <jovieira@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/27 21:15:22 by jovieira      #+#    #+#                 */
/*   Updated: 2024/02/05 14:57:35 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/token.h"

t_token	*ft_lstlast(t_token *lst)
{
	while (lst != NULL && lst->next)
		lst = lst->next;
	return (lst);
}

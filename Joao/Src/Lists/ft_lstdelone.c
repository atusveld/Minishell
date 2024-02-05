/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstdelone_bonus.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: jovieira <jovieira@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/27 22:01:09 by jovieira      #+#    #+#                 */
/*   Updated: 2024/02/05 14:57:26 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/token.h"

void	ft_lstdelone(t_token *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	free(lst);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstclear.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jovieira <jovieira@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/30 15:30:48 by jovieira      #+#    #+#                 */
/*   Updated: 2024/04/08 13:13:56 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/parse.h"

void	ft_redir_clean(t_red **lst)
{
	t_red	*temp;

	if (!lst)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		ft_redir_del(*lst);
		*lst = temp;
	}
}
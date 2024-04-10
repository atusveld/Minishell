/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstadd_back.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jovieira <jovieira@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/27 21:34:46 by jovieira      #+#    #+#                 */
/*   Updated: 2024/04/08 14:14:04 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/parse.h"

void	ft_add_redir(t_red **lst, t_red *new)
{
	t_red	*tail;

	if (!lst)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	tail = ft_redir_last(*lst);
	tail->next = new;
}

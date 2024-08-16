/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_add_redir.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jovieira <jovieira@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/27 21:34:46 by jovieira      #+#    #+#                 */
/*   Updated: 2024/08/06 14:21:59 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

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

void	ft_add_parse(t_parse **lst, t_parse *new)
{
	t_parse	*tail;

	if (!lst)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	tail = ft_parse_last(*lst);
	tail->next = new;
}

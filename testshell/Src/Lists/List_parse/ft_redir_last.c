/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_redir_last.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jovieira <jovieira@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/27 21:15:22 by jovieira      #+#    #+#                 */
/*   Updated: 2024/05/22 12:00:15 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/parse.h"

t_red	*ft_redir_last(t_red *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

t_parse	*ft_parse_last(t_parse *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}
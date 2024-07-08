/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstdelone.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jovieira <jovieira@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/27 22:01:09 by jovieira      #+#    #+#                 */
/*   Updated: 2024/04/08 13:14:00 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/parse.h"

void	ft_redir_del(t_red *lst)
{
	if (!lst)
		return ;
	free(lst);
}

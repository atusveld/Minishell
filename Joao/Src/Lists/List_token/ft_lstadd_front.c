/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstadd_front_bonus.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jovieira <jovieira@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/27 20:22:15 by jovieira      #+#    #+#                 */
/*   Updated: 2024/02/05 14:57:08 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/token.h"

void	ft_lstadd_front(t_token **lst, t_token *new)
{
	if (lst && new)
		new->next = *lst;
	*lst = new;
}

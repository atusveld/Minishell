/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstnew_bonus.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jovieira <jovieira@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/27 19:30:10 by jovieira      #+#    #+#                 */
/*   Updated: 2024/02/05 14:57:46 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/token.h"

t_token	*ft_lstnew(void *content)
{
	t_token	*head;

	head = malloc(sizeof(t_token));
	if (head == NULL)
		return (NULL);
	head->content = content;
	head->next = NULL;
	return (head);
}

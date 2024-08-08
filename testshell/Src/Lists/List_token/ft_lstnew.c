/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstnew.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jovieira <jovieira@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/27 19:30:10 by jovieira      #+#    #+#                 */
/*   Updated: 2024/08/06 17:36:37 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/main.h"

t_token	*ft_lstnew(void *content)
{
	t_token	*head;

	head = malloc(sizeof(t_token));
	if (head == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	head->cont = content;
	head->next = NULL;
	return (head);
}

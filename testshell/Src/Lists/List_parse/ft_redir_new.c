/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_redir_new.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jovieira <jovieira@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/27 19:30:10 by jovieira      #+#    #+#                 */
/*   Updated: 2024/08/06 14:21:43 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_red	*ft_redir_new(char *filename, t_type type)
{
	t_red	*head;

	head = malloc(sizeof(t_red));
	if (head == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	head->filename = filename;
	head->type = type;
	head->next = NULL;
	return (head);
}

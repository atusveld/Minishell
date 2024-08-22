/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_redir_new.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jovieira <jovieira@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/27 19:30:10 by jovieira      #+#    #+#                 */
/*   Updated: 2024/08/21 18:30:26 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

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
	free(filename);// leaking?
	head->type = type;
	head->next = NULL;
	return (head);
}

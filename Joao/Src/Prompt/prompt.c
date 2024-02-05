/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   prompt.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jovieira <jovieira@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/24 14:13:50 by jovieira      #+#    #+#                 */
/*   Updated: 2024/02/02 16:53:57 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "token.h"
#include <readline/readline.h>
#include <readline/history.h>

int	main(int argv, char **argc, char **envp)
{
	t_token	*token;

	(void)argv;
	(void)argc;
	(void)envp;

	token = malloc(sizeof(t_token));
	while (1)
	{
		token->input = readline("Minishell: ");
		add_history(token->input);
		// printf("%s\n", token->line);
		asign_token(token);
	}
	return (0);
}

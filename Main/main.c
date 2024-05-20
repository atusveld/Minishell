/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jovieira <jovieira@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/10 16:42:04 by jovieira      #+#    #+#                 */
/*   Updated: 2024/04/10 16:42:22 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../Joao/Includes/token.h"
#include "../Joao/Includes/lexer.h"
#include "../Joao/Includes/parse.h"

int	main(int argv, char **argc, char **envp)
{
	t_data	*input;
	t_token	*token;

	(void)argv;
	(void)argc;
	(void)envp;
	input = malloc(sizeof(t_data));
	token = ft_calloc(1, sizeof(t_token));
	token->next = NULL;
	while (1)
	{
		input->input = readline("Minishell: ");
		add_history(input->input);
		input->input = ft_strtrim(input->input, "\n\t\f\v ");
		token = ft_token(input->input);
		asign_token(token);
		if (lexer(token) == 1)
			continue ;
		parse(token);
	}
	return (0);
}

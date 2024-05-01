/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jovieira <jovieira@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/24 13:15:34 by jovieira      #+#    #+#                 */
/*   Updated: 2024/01/24 13:15:35 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/token.h"
#include "Includes/lexer.h"
#include "Includes/parse.h"
#include "Includes/alex.h"

int	main(int argv, char **argc, char **envp)
{
	t_data	*input;
	t_token	*token;
	t_parse	*parsed;
	t_gen	gen;

	(void)argv;
	(void)argc;
	(void)envp;
	input = malloc(sizeof(t_data));
	token = ft_calloc(1, sizeof(t_token));
	token->next = NULL;
	gen.env = ft_build_env(envp);
	while (1)
	{
		input->input = readline("Minishell: ");
		add_history(input->input);
		input->input = ft_strtrim(input->input, "\n\t\f\v ");
		token = ft_token(input->input);
		asign_token(token);
		if (lexer(token) == 1)
			continue ;
		parsed = parse(token);
		ft_init(parsed, &gen);
	}
	ft_free_env(&gen.env);
	return (0);
}

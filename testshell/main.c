/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jovieira <jovieira@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/24 13:15:34 by jovieira      #+#    #+#                 */
/*   Updated: 2024/05/22 14:23:45 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/main.h"

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
		if (!input->input)
			return (1);
		input->input = ft_strtrim(input->input, "\n\t\f\v ");
		if (ft_strlen(input->input) == 0)
			continue ;
		add_history(input->input);
		token = ft_token(input->input);
		asign_token(token);
		if (lexer(token) == 1)
			continue ;
		parsed = parse(token, gen.env);
		ft_exe(parsed, &gen);
	}
	// ft_free_gen(&gen);
	return (0);
}

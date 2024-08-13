/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jovieira <jovieira@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/24 13:15:34 by jovieira      #+#    #+#                 */
/*   Updated: 2024/08/13 17:02:26 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/main.h"

t_main	*par_init(char **envp, t_main *main)
{
	main = malloc(sizeof(t_main));
	main->env = ft_build_env(envp);
	main->parsed = NULL;
	main->input = malloc(sizeof(t_data));
	main->token = ft_calloc(1, sizeof(t_token));
	main->token->next = NULL;
	main->gen = malloc(sizeof(t_gen));
	main->gen->env_paths = get_paths(main);
	main->gen->e_code = 0;
	return (main);
}

int	main(int argv, char **argc, char **envp)
{
	t_main	*main;

	main = NULL;
	(void)argv;
	(void)argc;
	main = par_init(envp, main);
	while (1)
	{
		main->input->input = readline("Minishell: ");
		if (!main->input->input)
			return (1);
		main->input->input = ft_strtrim(main->input->input, "\n\t\f\v ");
		if (ft_strlen(main->input->input) == 0)
			continue ;
		add_history(main->input->input);
		main->token = ft_token(main->input->input);
		asign_token(main->token);
		if (lexer(main->token) == 1)
			continue ;
		parse(main);
		ft_exe(main->parsed, main);
		free(main->parsed);
		main->parsed = NULL;
	}
	// ft_free_gen(&gen);
	return (0);
}

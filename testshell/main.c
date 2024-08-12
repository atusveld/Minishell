/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jovieira <jovieira@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/24 13:15:34 by jovieira      #+#    #+#                 */
/*   Updated: 2024/08/08 17:46:23 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/main.h"

int	main(int argv, char **argc, char **envp)
{
	t_main	*main;

	main = NULL;
	(void)argv;
	(void)argc;
	// (void)envp;
	main = init_main(envp, main);
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
		main->parsed = parse(main->token, main->env);
		// main->gen->cmd_args = main->parsed->argv;
		ft_exe(main->parsed, main);
	}
	// ft_free_gen(&gen);
	return (0);
}

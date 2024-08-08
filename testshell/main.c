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
#include "Includes/alex.h"

int	main(int argv, char **argc, char **envp)
{
<<<<<<< HEAD
	t_main	*main;
=======
	t_data	*input;
	t_token	*token;
	t_parse	*parsed;
	t_gen	*gen;
>>>>>>> c3aecb263a7c5383cfc3f28adc8d242fac8f04ab

	main = NULL;
	(void)argv;
	(void)argc;
<<<<<<< HEAD
	// (void)envp;
	main = init_main(envp, main);
=======
	(void)envp;
	input = malloc(sizeof(t_data));
	token = ft_calloc(1, sizeof(t_token));
	token->next = NULL;
	gen = NULL;
	gen->env = ft_build_env(envp);
>>>>>>> c3aecb263a7c5383cfc3f28adc8d242fac8f04ab
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
<<<<<<< HEAD
		main->parsed = parse(main->token, main->env);
		// main->gen->cmd_args = main->parsed->argv;
		ft_exe(main->parsed, main);
=======
		parsed = parse(token, gen->env);
		if (gen == NULL)
			gen = ft_init(parsed, gen);
		ft_exe(parsed, gen);
>>>>>>> c3aecb263a7c5383cfc3f28adc8d242fac8f04ab
	}
	// ft_free_gen(&gen);
	return (0);
}

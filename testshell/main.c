/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jovieira <jovieira@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/24 13:15:34 by jovieira      #+#    #+#                 */
/*   Updated: 2024/08/15 16:42:26 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/main.h"

t_main	*par_init(char **envp, t_main *main)
{
	main = ft_calloc(1, sizeof(t_main));
	main->env = ft_build_env(envp);
	main->input = malloc(sizeof(t_data));
	main->gen = malloc(sizeof(t_gen));
	main->gen->env_paths = get_paths(main);
	main->gen->e_code = 0;
	return (main);
}

void	main_clean(t_main *main)
{
	t_env *tmp;
	int i;

	i = 0;
	while (main->env)
	{
		tmp = main->env->next;
		free(main->env->key);
		printf("val: %s\n", main->env->val);
		free(main->env->val);
		free(main->env->str);
		free(main->env);
		main->env = tmp;
	}
	rl_clear_history();
	while(main->gen->env_paths[i] != NULL)
	{
		free(main->gen->env_paths[i]);
		i++;
	}
	free(main->gen->env_paths);
	free(main->input);
	free(main->gen);
	free(main);
}

void	parse_clean(t_main *main)
{
	t_parse *tmp;
	int i;

	while (main->parsed)
	{
		i = 0;
		tmp = main->parsed->next;
		// while (main->parsed->argv[i++])
		while (main->parsed->argv[i] != NULL)
		{
			free(main->parsed->argv[i]);
			i++;
		}
		free(main->parsed->argv);
		free(main->parsed);
		main->parsed = tmp;
	}
}

int	main(int argv, char **argc, char **envp)
{
	t_main	*main;
	char *tmp;

	main = NULL;
	(void)argv;
	(void)argc;
	main = par_init(envp, main);
	ignore_signal();
	unset_signals(0);
	while (1)
	{
		main->input->input = readline("Minishell: ");
		if (!main->input->input)
		{
			// 	t_env *tmp;

			// while (main->env)
			// {
			// tmp = main->env->next;
			// free(main->env->key);
			// free(main->env->val);
			// free(main->env->str);
			// free(main->env);
			// main->env = tmp;
			// }
			// free(main->input->input);
			// free(main->input);
			// free(main);
			break ;
		}
		tmp = main->input->input;
		main->input->input = ft_strtrim(main->input->input, "\n\t\f\v ");
		free(tmp);
		if (ft_strlen(main->input->input) == 0)
			continue ;
		add_history(main->input->input);
		main->token = ft_token(main->input->input);
		free(main->input->input);
		asign_token(main->token);
		if (lexer(main->token) == 1)
			continue ;
		parse(main);
		ft_lstclear_mod(&main->token);
		ft_exe(main->parsed, main);
		parse_clean(main);
	}
	main_clean(main);
	set_signals();
	return (0);
}

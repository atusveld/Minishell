/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jovieira <jovieira@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/24 13:15:34 by jovieira      #+#    #+#                 */
/*   Updated: 2024/08/16 15:20:32 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/shell.h"

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
	t_shell *shell;
	char *tmp;

	shell = NULL;
	(void)argv;
	(void)argc;
	shell = init_shell(envp, shell);
	ignore_signal();
	unset_signals(0);
	while (1)
	{
		shell->input->input = readline("Minishell: ");
		if (!shell->input->input)
			return (1);
		shell->input->input = ft_strtrim(shell->input->input, "\n\t\f\v ");
		if (ft_strlen(shell->input->input) == 0)
			continue ;
		add_history(shell->input->input);
		shell->token = ft_token(shell->input->input);
		free(main->input->input);
		asign_token(shell->token);
		if (lexer(shell->token) == 1)
			continue ;
		shell->parsed = parse(shell->token, shell->env);
		ft_exe(shell->parsed, shell);
	}
	main_clean(main);
	set_signals();
	return (0);
}

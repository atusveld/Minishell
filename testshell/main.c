/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jovieira <jovieira@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/24 13:15:34 by jovieira      #+#    #+#                 */
/*   Updated: 2024/08/20 10:15:18 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/shell.h"

// t_shell	*init_shell(char **envp, t_shell *shell)
// {
// 	shell = ft_calloc(1, sizeof(t_shell));
// 	shell->env = ft_build_env(envp);
// 	shell->input = malloc(sizeof(t_data));
// 	shell->gen = malloc(sizeof(t_gen));
// 	shell->gen->env_paths = get_paths(shell);
// 	shell->gen->e_code = 0;
// 	return (shell);
// }

void	main_clean(t_shell *shell)
{
	t_env *tmp;
	int i;

	i = 0;
	while (shell->env)
	{
		tmp = shell->env->next;
		free(shell->env->key);
		// printf("val: %s\n", shell->env->val);
		free(shell->env->val);
		free(shell->env->str);
		free(shell->env);
		shell->env = tmp;
	}
	rl_clear_history();
	while(shell->gen->env_paths[i] != NULL)
	{
		free(shell->gen->env_paths[i]);
		i++;
	}
	free(shell->gen->env_paths);
	free(shell->input);
	free(shell->gen);
	free(shell);
}

void	parse_clean(t_shell *shell)
{
	t_parse *tmp;
	int i;

	while (shell->parsed)
	{
		i = 0;
		tmp = shell->parsed->next;
		while (shell->parsed->argv[i] != NULL)
		{
			free(shell->parsed->argv[i]);
			i++;
		}
		free(shell->parsed->argv);
		free(shell->parsed);
		shell->parsed = tmp;
	}
}

void	print_env(t_shell	*shell) {
	t_env *tmp = shell->env;
	while (tmp) {
		printf("key: %s", tmp->key);
		printf(": val: %s\n", tmp->val);
		tmp = tmp->next;
	}
}

int	main(int argv, char **argc, char **envp)
{
	t_shell *shell;

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
			ft_error("Parsing error, main", shell, 1);
		shell->input->input = ft_strtrim(shell->input->input, "\n\t\f\v ");// still leaks
		if (ft_strlen(shell->input->input) == 0)
			continue ;
		add_history(shell->input->input);
		shell->token = ft_token(shell->input->input);
		free(shell->input->input);
		asign_token(shell->token);
		if (lexer(shell->token) == 1)
			continue ;
		parse(shell);
		ft_exe(shell->parsed, shell);
		parse_clean(shell);
	}
	main_clean(shell);
	set_signals();
	return (0);
}

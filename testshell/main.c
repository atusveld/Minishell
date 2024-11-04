/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jovieira <jovieira@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/24 13:15:34 by jovieira      #+#    #+#                 */
/*   Updated: 2024/08/22 12:05:40 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/shell.h"

void	main_clean(t_shell *shell)
{
	t_env *tmp;
	int i;

	i = 0;
	while (shell->env)
	{
		tmp = shell->env->next;
		free(shell->env->key);
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
			
int	ft_readline(t_shell *shell)
{
	char *line_tmp;
	char *line;

	line_tmp = readline("Minishell: ");
	if (!line_tmp)
		ft_error("Parsing error, main", shell, 1);
	line = ft_strtrim(line_tmp, "\n\t\f\v ");
	if (ft_strlen(line) == 0)
		return (1);
	add_history(line_tmp);
	free(line_tmp);
	printf("line: %s\n", line);
	shell->token = ft_token(line);
	printf("token: %s\n", shell->token->cont);
	free(line);
	return (0);
}

int	lexing(t_shell *shell)
{
	asign_token(shell->token);
	if (lexer(shell->token))
		return (1);
	return (0);
}

int	main(int argv, char **argc, char **envp)
{
	t_shell *shell;

	(void)argv;
	(void)argc;
	shell = NULL;
	shell = init_shell(envp, shell);
	ignore_signal();
	unset_signals(0);
	while (1)
	{
		if (ft_readline(shell))
			continue ;
		// ----------------------------------------
		if (lexing(shell))
			continue;
		// -----------------------------------------
		parse(shell);
		ft_exe(shell->parsed, shell);
		parse_clean(shell);
		// break;
	}
	// printf("cleaning\n");
	main_clean(shell);
	set_signals();
	return (0);
}

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

#include "Includes/shell.h"

int	main(int argv, char **argc, char **envp)
{
	t_shell *shell;

	shell = NULL;
	(void)argv;
	(void)argc;
	shell = init_shell(envp, shell);
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
		asign_token(shell->token);
		if (lexer(shell->token) == 1)
			continue ;
		shell->parsed = parse(shell->token, shell->env);
		ft_exe(shell->parsed, shell);
	}
	return (0);
}

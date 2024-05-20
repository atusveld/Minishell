/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: atusveld <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/03 15:26:55 by atusveld      #+#    #+#                 */
/*   Updated: 2024/04/10 16:48:10 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>

int	main(int argc, char **argv, char **envp)
{
	char *cmd[3];
	cmd[0] = "ls";
	cmd[1] = "-l";
	cmd[2] = NULL;
	char * const one = "/bin/ls";
	execve(one, cmd, envp);
	
	// t_gen	*gen;
	// ft_init(gen);
	// suppress_sig_output();
	// signal(SIGINT, sig_func_parent);
	// signal(SIGQUIT, SIG_IGN);
	// minishell(&env);
}
// static void	minishell(t_env **env)
// {
// 	char	*line;
	
// 	while (1)
// 	{
// 		line = readline("CRLsHellO");

// 		if (line[0] == '\0')
// 		{
// 			free (line);
// 			continue;
// 		}
// 	}
// }

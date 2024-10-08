/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                      	                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: atusveld <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/03 15:26:55 by atusveld      #+#    #+#                 */
/*   Updated: 2022/09/07 17:40:34 by atusveld      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/shell.h"

t_shell	*init_shell(char **envp, t_shell *shell)
{
	shell = ft_calloc(1, sizeof(t_shell));
	shell->env = ft_build_env(envp);
	shell->gen = malloc(sizeof(t_gen));
	shell->gen->env_paths = get_paths(shell);
	shell->gen->e_code = 0;
	return (shell);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins_util.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: atusveld <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/03 15:26:55 by atusveld      #+#    #+#                 */
/*   Updated: 2024/08/13 17:25:27 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/shell.h"

int	ft_if_builtin(t_shell *shell)
{
	if ((ft_strncmp(shell->gen->cmd_args[0], "echo", 5)) == 0)
	{
		if (shell->parsed->redir_in)
			return (ft_red_in(shell), shell->gen->e_code);
		if (shell->parsed->redir_out)
			return (ft_red_out(shell), shell->gen->e_code);
		else
			return (ft_echo(shell), shell->gen->e_code);
	}
	if (!ft_strncmp(shell->gen->cmd_args[0], "pwd", 4))
		return (ft_pwd(shell), shell->gen->e_code);
	if (!ft_strncmp(shell->gen->cmd_args[0], "env", 4))
		return (ft_env(shell), shell->gen->e_code);
	if (!ft_strncmp(shell->gen->cmd_args[0], "cd", 3))
		return (ft_cd(shell), shell->gen->e_code);
	if (!ft_strncmp(shell->gen->cmd_args[0], "exit", 5))
		return (ft_exit(shell), shell->gen->e_code);
	if (!ft_strncmp(shell->gen->cmd_args[0], "unset", 6))
		return (ft_unset(shell, shell->gen->cmd_args + 1), shell->gen->e_code);
	if (!ft_strncmp(shell->gen->cmd_args[0], "export", 7))
		return (ft_export(shell), shell->gen->e_code);
	return (1);
}

void	ft_cd_update_env(t_shell *shell, char *old_p, char *new_p)
{
	if (ft_find_env(shell->env, "OLD_PWD"))
		ft_add_envtry(shell->env, "OLD_PWD", old_p);
	if (ft_find_env(shell->env, "NEW_PWD"))
		ft_add_envtry(shell->env, "NEW_PWD", new_p);
}

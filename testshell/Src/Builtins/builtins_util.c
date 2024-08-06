/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins_util.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: atusveld <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/03 15:26:55 by atusveld      #+#    #+#                 */
/*   Updated: 2022/09/07 17:40:34 by atusveld      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/alex.h"

int	ft_if_builtin(t_gen *gen, t_parse *parsed)
{
	if ((ft_strncmp(gen->cmd_args[0], "echo", 5)) == 0)
	{
		if (parsed->redir_in)
			return (ft_red_in(parsed, gen), 0);
		if (parsed->redir_out)
			return (ft_red_out(parsed, gen), 0);
		else
			return (ft_echo(gen), 0);
	}
	if (!ft_strncmp(gen->cmd_args[0], "pwd", 4))
		return (ft_pwd(gen), 0);
	if (!ft_strncmp(gen->cmd_args[0], "env", 4))
		return (ft_env(gen), 0);
	if (!ft_strncmp(gen->cmd_args[0], "cd", 3))
		return (ft_cd(gen), 0);
	if (!ft_strncmp(gen->cmd_args[0], "exit", 5))
		return (ft_exit(parsed), 0);
	if (!ft_strncmp(gen->cmd_args[0], "unset", 6))
		return (ft_unset(gen, gen->cmd_args + 1), 0);
	if (!ft_strncmp(gen->cmd_args[0], "export", 7))
		return (ft_export(gen, gen->cmd_args + 1), 0);
	return (1);
}

void	ft_cd_update_env(t_gen *gen, char *old_p, char *new_p)
{
	if (ft_find_env(gen->env, "OLD_PWD"))
		ft_add_envtry(gen->env, "OLD_PWD", old_p);
	if (ft_find_env(gen->env, "NEW_PWD"))
		ft_add_envtry(gen->env, "NEW_PWD", new_p);
}

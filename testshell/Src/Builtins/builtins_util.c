/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins_util.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: atusveld <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/03 15:26:55 by atusveld      #+#    #+#                 */
/*   Updated: 2024/08/08 17:37:38 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/main.h"

int	ft_if_builtin(t_main *main, t_parse *parsed)
{
	if ((ft_strncmp(main->gen->cmd_args[0], "echo", 5)) == 0)
	{
		if (parsed->redir_in)
			return (ft_red_in(parsed, main), 0);
		if (parsed->redir_out)
			return (ft_red_out(parsed, main), 0);
		else
			return (ft_echo(main), 0);
	}
	if (!ft_strncmp(main->gen->cmd_args[0], "pwd", 4))
		return (ft_pwd(main), 0);
	if (!ft_strncmp(main->gen->cmd_args[0], "env", 4))
		return (ft_env(main), 0);
	if (!ft_strncmp(main->gen->cmd_args[0], "cd", 3))
		return (ft_cd(main), 0);
	if (!ft_strncmp(main->gen->cmd_args[0], "exit", 5))
		return (ft_exit(parsed), 0);
<<<<<<< HEAD
	if (!ft_strncmp(main->gen->cmd_args[0], "unset", 6))
		return (ft_unset(main->env, main->gen->cmd_args + 1), 0);
	if (!ft_strncmp(main->gen->cmd_args[0], "export", 7))
		return (ft_export(main), 0);
=======
	if (!ft_strncmp(gen->cmd_args[0], "unset", 6))
		return (ft_unset(gen, gen->cmd_args + 1), 0);
	if (!ft_strncmp(gen->cmd_args[0], "export", 7))
		return (ft_export(gen, gen->cmd_args + 1), 0);
>>>>>>> c3aecb263a7c5383cfc3f28adc8d242fac8f04ab
	return (1);
}

void	ft_cd_update_env(t_main *main, char *old_p, char *new_p)
{
	if (ft_find_env(main->env, "OLD_PWD"))
		ft_add_envtry(main->env, "OLD_PWD", old_p);
	if (ft_find_env(main->env, "NEW_PWD"))
		ft_add_envtry(main->env, "NEW_PWD", new_p);
}

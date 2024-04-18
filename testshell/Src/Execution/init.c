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

#include "../../Includes/exec.h"
#include "../../Includes/env.h"

void	ft_init(t_gen *gen, t_parse *parsed)
{
	gen->cmd_args = parsed->argv;
	gen->env_paths = get_paths(gen);
	gen->cmd_path = get_cmd_path(gen);
}
// t_env	*ft_init_env(char **envp)
// {
// 	t_env	*new_env;
// 	char	*tmp;

// 	new_env = ft_env_cpy(envp);
// 	tmp = getcwd(NULL, 0);
// 	if (!tmp)
// 		ft_error("env");
// }
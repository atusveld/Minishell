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

#include "minishell.h"

void	ft_init(t_gen *gen)
{
	// init gen->cmd_args
	gen->env_paths = get_paths(gen);
	gen->cmd_path = get_cmd_path(gen);
}

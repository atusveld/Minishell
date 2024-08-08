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

#include "../../Includes/alex.h"

t_gen	*ft_init(t_parse *parsed, t_gen *gen)
{
	printf("=[INITTED]=");

	gen->env_paths = get_paths(gen);
	gen->cmd_args = parsed->argv;
	gen->cmd_path = get_cmd_path(gen);
	gen->owd = getcwd(NULL, 0);
	gen->e_code = 0;
	return (gen);
}

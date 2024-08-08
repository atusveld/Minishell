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

#include "../../Includes/main.h"

// void	par_init(char **envp)
// {
// 	t_data	*input;
// 	t_token	*token;
// 	t_parse	*parsed;
// 	t_gen	gen;

// 	input = malloc(sizeof(t_data));
// 	token = ft_calloc(1, sizeof(t_token));
// 	token->next = NULL;
// 	gen.env = ft_build_env(envp);
// }

void	exe_init(t_parse *parsed, t_gen *gen)
{	
	gen->cmd_args = parsed->argv;
	gen->env_paths = get_paths(gen);
	gen->cmd_path = get_cmd_path(gen);
	gen->e_code = 0;
	printf("exp_data %i\n", gen->e_code);
	gen->owd = getcwd(NULL, 0);
}

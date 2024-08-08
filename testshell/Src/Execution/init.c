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

<<<<<<< HEAD
t_main	*init_main(char **envp, t_main *main)
{
	main = malloc(sizeof(t_main));
	main->parsed = NULL;
	main->input = malloc(sizeof(t_data));
	main->token = ft_calloc(1, sizeof(t_token));
	main->token->next = NULL;
	main->gen = malloc(sizeof(t_gen));
	main->env = ft_build_env(envp);
	main->gen->env_paths = get_paths(main);
	main->gen->e_code = 0;
	return (main);
=======
t_gen	*ft_init(t_parse *parsed, t_gen *gen)
{
	printf("=[INITTED]=");

	gen->env_paths = get_paths(gen);
	gen->cmd_args = parsed->argv;
	gen->cmd_path = get_cmd_path(gen);
	gen->owd = getcwd(NULL, 0);
	gen->e_code = 0;
	return (gen);
>>>>>>> c3aecb263a7c5383cfc3f28adc8d242fac8f04ab
}

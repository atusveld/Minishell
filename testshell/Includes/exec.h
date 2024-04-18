/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec.h                               		        :+:    :+:            */
/*                                                     +:+                    */
/*   By: atusveld <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/03 15:26:55 by atusveld      #+#    #+#                 */
/*   Updated: 2022/09/07 17:40:34 by atusveld      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

//==========[ EXEC_H ]==========//
#ifndef EXEC_H
#define EXEC_H
//==========[ LIBRARIES ]==========//
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdbool.h>
#include "token.h"
#include "parse.h"
#include "lexer.h"
//==========[ STRUCTS ]==========//
typedef	struct s_gen
{
	char	**env_paths;
	char	**cmd_args;
	char	*cmd_path;
}	t_gen;

typedef struct s_pipe
{
	int	tube[2];
	int	in_fd;
	int	*pid;
	int	i;
}	t_pipe;

//==========[ PROTOTYPES ]==========//
void	ft_init(t_gen *gen, t_parse *parsed);
void	ft_error(char *str);
int	new_process(t_parse *parse, t_gen *gen, char **envp);
// static t_pipe	ft_init_pipe(int size);
#endif
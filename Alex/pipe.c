/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipe.c                	                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: atusveld <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/03 15:26:55 by atusveld      #+#    #+#                 */
/*   Updated: 2022/09/07 17:40:34 by atusveld      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_pipe	*init_pipe(int size)
{
	t_pipe	*new_pipe;

	new_pipe = (t_pipe *)malloc(1 * sizeof(t_pipe));
	if (!new_pipe)
		ft_error(pipe);
	new_pipe->pid = (int *)malloc((size) * sizeof(int));
	if (!new_pipe->pid)
		ft_error(pipe);
	new_pipe->in_fd = STDIN_FILENO;
	new_pipe->i = -1;
	return (new_pipe);
}

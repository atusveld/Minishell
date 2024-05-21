/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   child.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: atusveld <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/03 15:26:55 by atusveld      #+#    #+#                 */
/*   Updated: 2024/05/20 11:09:48 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/alex.h"

t_cpro	*ft_init_cpro(void)
{
	t_cpro	*new_cpro;

	new_cpro = (t_cpro *)malloc(1 * sizeof(t_cpro));
	if (!new_cpro)
		ft_error("cpro");
	new_cpro->pid = fork();
	if (!new_cpro->pid)
		ft_error("cpro pid");
	new_cpro->in_fd = STDIN_FILENO;
	new_cpro->i = -1;
	return (new_cpro);
}

void	ft_free_cpro(t_cpro *cpro)
{
	// free(cpro->pid);
	free(cpro);
}

int	ft_count_cmd(t_parse *parsed)
{
	int	i;
	t_parse	*tmp;

	i = 0;
	tmp = parsed;
	while (tmp != NULL)
	{
		tmp = tmp->next;
		i++;
	}
	free(tmp);
	return (i);
}
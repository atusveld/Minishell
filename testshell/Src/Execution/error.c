/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                 	        :+:    :+:            */
/*                                                     +:+                    */
/*   By: atusveld <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/03 15:26:55 by atusveld      #+#    #+#                 */
/*   Updated: 2022/09/07 17:40:34 by atusveld      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/main.h"

void	ft_error(char *str, int e_code)
{
	perror(str);
	exit (e_code);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: atusveld <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/03 15:26:55 by atusveld      #+#    #+#                 */
/*   Updated: 2022/09/07 17:40:34 by atusveld      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

//==========[  ]==========//
#ifndef SHELL_H
#define SHELL_H

//==========[  ]==========//
#include <stdio.h>
#include <unistd.h>

//==========[  ]==========//
void shell_interactive(void);
void shell_no_interactive(void);

#endif
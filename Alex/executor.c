/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: atusveld <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/03 15:26:55 by atusveld      #+#    #+#                 */
/*   Updated: 2022/09/07 17:40:34 by atusveld      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int new_process(char **args)
{
 pid_t pid;
 int status;

 pid = fork();
 if (pid ==  0)
 {
  if (execvp(args[0], args) == -1)
  {
   perror("child error");
  }
  exit(EXIT_FAILURE);
 }
 else if (pid < 0)
 {
  perror("fork error");
 }
 else
 {
  do {
   waitpid(pid, &status, WUNTRACED);
  } while (!WIFEXITED(status) && !WIFSIGNALED(status));
 }
 return (-1);
}
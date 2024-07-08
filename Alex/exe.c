/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exe.c           	                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: atusveld <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/03 15:26:55 by atusveld      #+#    #+#                 */
/*   Updated: 2022/09/07 17:40:34 by atusveld      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int new_process(t_gen *gen, char **envp)
{
 pid_t 	pid;
 int 	status;

 pid = fork();
 if (pid ==  0)
 {
  if (execve(gen->cmd_path, gen->cmd_args, envp) == -1)
  {
  	perror("child error");
	exit (EXIT_FAILURE);
  }
 }
 else if (pid < 0)
 {
	perror("fork fail");
    exit(1);
 }
 else
 {
	while (!WIFEXITED(status) && !WIFSIGNALED(status))
		waitpid(pid, &status, WUNTRACED);
 }
 return (-1);
}

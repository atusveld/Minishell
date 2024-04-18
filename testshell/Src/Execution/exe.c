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

#include "../../Includes/exec.h"

int new_process(t_parse *parsed, t_gen *gen, char **envp)
{
	ft_init(gen, parsed);
	execve(gen->cmd_path, gen->cmd_args, envp);
//  pid_t 	pid;
//  int 	status;

//  pid = fork();
//  if (pid ==  0)
//  {
//   if (execve(*parse->argv, &parse->argv[0], envp) == -1)
//   {
//   	perror("child error");
// 	exit (EXIT_FAILURE);
//   }
//  }
//  else if (pid < 0)
//  {
// 	perror("fork fail");
//     exit(1);
//  }
//  else
//  {
// 	while (!WIFEXITED(status) && !WIFSIGNALED(status))
// 		waitpid(pid, &status, WUNTRACED);
//  }
 return (-1);
}

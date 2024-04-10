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

// int execute_args(char **args)
// {
// 	int	i;
//  	char *builtin_func_list[] = 
//  	{
// 		"cd",
// 		"env",
// 		"help",
// 		"exit"
//  	};

//  int (*builtin_func[])(char **) = 
//  {
//   &OUR_cd,
//   &OUR_env,
//   &OUR_help,
//   &OUR_exit
//  }
//  i = 0;

//  if (args[0] == NULL)
//   return (-1);
//  while (i < sizeof(builtin_func_list) / sizeof(char *))
//  {
// 	i++;
// 	if (strcmp(args[0], builtin_func_list[i]) == 0)
// 		return ((*builtin_func[i])(args));
//  }
//  return (new_process(args));
// }
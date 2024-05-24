/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   aux.c                      	                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: atusveld <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/03 15:26:55 by atusveld      #+#    #+#                 */
/*   Updated: 2022/09/07 17:40:34 by atusveld      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
 
 #include "../../Includes/alex.h"

 char	*ft_strjoin_three(char *s1, char *s2, char *s3)
 {
	char	*temp;
	char	*str;

	temp = ft_strjoin(s1, s2);
	str = ft_strjoin(temp, s3);
	free (temp);
	return (str);
 }

void	*ft_free_arr(char **arr)
 {
	int	i;

	i = 0;
	if (!arr)
		return (NULL);
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (NULL);
 }
 
//  int	ft_count_cmd(t_gen *gen, t_parse *parsed)
//  {
// 	int	i;

// 	i = 0;
// 	if (!parsed->next)
// 		return (-1);
// 	while (parsed->next)
// 		i++;
// 	return (i);
//  }

 //ft_exe_multi_legacy
	// t_cpro	*cpro;
	// int		fd;
	// int		i;
	// int		j;

	// i = 0;
	// j = ft_count_cmd(parsed);
	// fd = ft_calloc(2, sizeof(int));
	// pipe(fd);
	// while (i < j)
	// {
	// 	cpro = ft_init_cpro();
	// 	if (cpro->pid == -1)
	// 		ft_error("child");
	// 	else if (cpro->pid == 0)
	// 	{
			
	// 	}
	// }
	// return (1);

// int	ft_exe_multi(t_gen *gen, t_parse *parsed)
// {
// 	// char	*path;
// 	int		status;
// 	int		cmd_c;
// 	int		i;
// 	// int		fd[2];
// 	pid_t	pid[2];

// 	i = 0;
// 	cmd_c = ft_count_cmd(parsed);
// 	status = -1;
// 	while (cmd_c > i)
// 	{
// 		// pid[i] = fork();
// 		// if (pipe(fd) < 0)
// 		// 	ft_error("pipe");
// 		// if (pid[i] < 0)
// 		// 	ft_error("fork");
// 		// gen->cmd_args = parsed->argv;
// 		// path = get_cmd_path(gen);
// 		// if (pid[i] == 0)
// 		// {
// 			if (i == 0)
// 			{
// 				dprintf(2, "==[HERE1]==\n");
// 				ft_exe_first(gen);
// 				// close(fd[0]);
// 				// dup2(fd[1], STDOUT_FILENO);
// 				// if ((execve(path, gen->cmd_args, ft_env_to_array(gen->env))) < 0)
// 				// 	ft_error("child");
// 			}
// 			else if (i != 0 && i != cmd_c - 1)
// 			{
// 				dprintf(2, "==[HERE2]==\n");
// 				ft_exe_mid(gen);
// 			// 	close(fd[1]);
// 			// 	dup2(fd[0], STDOUT_FILENO);
// 			// 	if ((execve(path, gen->cmd_args, ft_env_to_array(gen->env))) < 0)
// 			// 		ft_error("child");
// 			}
// 			else
// 			{
// 				dprintf(2, "==[HERE3]==\n");
// 				ft_exe_last(gen);
// 			// 	close(fd[1]);
// 			// 	dup2(fd[0], STDIN_FILENO);
// 			// 	if ((execve(path, gen->cmd_args, ft_env_to_array(gen->env))) < 0)
// 			// 		ft_error("child");
// 			}
// 		// }
// 		dprintf(2, "==[HERE4]==\n");
// 		i++;
// 		parsed = parsed->next;
// 	}
// 	i = 0;
// 	while (cmd_c > i)
// 	{
// 		dprintf(2, "==[HERE5]==\n");
// 		if (waitpid(pid[i], &status, WUNTRACED) == - 1)
// 			ft_error("pid");
// 		if (!WIFEXITED(status) && !WIFSIGNALED(status))
// 		i++;
// 	}
// 	return (-1);
// }

// i = 0;
	// while (cmd_c > i)
	// {
	// 	dprintf(2, "==[HERE5]==\n");
	// 	// if (waitpid(pid[i], &status, WUNTRACED) == - 1)
	// 	// 	ft_error("pid");
	// 	// if (!WIFEXITED(status) && !WIFSIGNALED(status))
	// 	i++;
	// }
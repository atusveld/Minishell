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
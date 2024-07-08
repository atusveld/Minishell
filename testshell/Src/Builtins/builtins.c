/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: atusveld <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/03 15:26:55 by atusveld      #+#    #+#                 */
/*   Updated: 2024/05/21 14:10:51 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/alex.h"

void	ft_echo(char **arr)
{
	bool nl;

	nl = true;
	if (!*arr)
		*arr = NULL;
	else if (!ft_strncmp(arr[0], "-n", 3))
	{
		nl = false;
		arr++;
	}
	while (*arr)
	{
		ft_putstr_fd(*arr, 1);
		if (*(arr + 1) && **arr)
			ft_putchar_fd(' ', 1);
		arr++;
	}
	if (nl)
		ft_putchar_fd('\n', 1);
}
void	ft_pwd(void)
{
	char	*temp;

	temp = getcwd(NULL, 0);
	printf("%s\n", temp);
	free (temp);
}
void	ft_env(t_gen *gen)
{
	t_env	*temp;

	temp = gen->env;
	while (temp)
	{
		if (temp->val && temp->key)
			printf("%s\n", temp->str);
		temp = temp->next;
	}
}

void	ft_cd(t_gen *gen)
{
	char	*old_p;
	char	*new_p;
	char	*path;
	
	old_p = getcwd(NULL, 0);
	path = ft_strjoin_three(old_p, "/", gen->cmd_args[1]);
	if (!path || !*path)
		path = ft_get_env(gen->env, "HOME"); // might want to set home to home of minishell project instead of home  of user
	if (chdir(path) == -1)
		perror("cd");
	new_p = getcwd(NULL, 0);
	ft_cd_update_env(gen, old_p, new_p);
	free (old_p);
	free (new_p);
	free (path);
}

void	ft_exit(t_parse *parsed) // check if first and last cmd per prompt -> no forky etc
{
	int	status;

	status = 0;
	if (parsed->next)
		printf("exit\n");
	exit(status);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: atusveld <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/03 15:26:55 by atusveld      #+#    #+#                 */
/*   Updated: 2024/08/08 17:37:03 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/main.h"

void	ft_echo(t_main *main)
{
	char	**arr;
	bool	nl;

	nl = true;
	arr = (main->gen->cmd_args + 1);
	if (!*arr)
	{
		ft_putchar_fd('\n', 1);
		return ;
	}
	if (!ft_strncmp(arr[0], "-n", 3))
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

void	ft_pwd(t_main *main)
{
	char	*temp;

	temp = getcwd(NULL, 0);
	if (!temp)
		ft_error("pwd", main);
	printf("%s\n", temp);
	free (temp);
}

void	ft_env(t_main *main)
{
	t_env	*temp;

	temp = main->env;
	if (!temp)
		ft_error("ft_env", main);
	while (temp)
	{
		if (temp->val && temp->key)
			printf("%s\n", temp->str);
		temp = temp->next;
	}
}

void	ft_cd(t_main *main)
{
	char	*old_p;
	char	*new_p;
	char	*path;

	old_p = getcwd(NULL, 0);
	if (!old_p)
		ft_error("no old pwd", main);
	path = ft_strjoin_three(old_p, "/", main->gen->cmd_args[1]);
	if (!path || !*path)
		path = ft_get_env(main->env, "HOME");
	if (chdir(path) == -1)
		perror("cd");
	new_p = getcwd(NULL, 0);
	if (!new_p)
		ft_error("cd", main);
	ft_cd_update_env(main, old_p, new_p);
	free (old_p);
	free (new_p);
	free (path);
}

void	ft_exit(t_parse *parsed)
{
	int	status;

	status = 0;
	if (parsed->next)
		printf("exit\n");
	exit(status);
}

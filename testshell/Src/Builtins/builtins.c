/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: atusveld <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/03 15:26:55 by atusveld      #+#    #+#                 */
/*   Updated: 2024/08/16 15:22:19 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/shell.h"

void	ft_echo(t_shell *shell)
{
	char	**arr;
	bool	nl;

	nl = true;
	arr = (shell->gen->cmd_args + 1);
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

void	ft_pwd(t_shell *shell)
{
	char	*temp;

	temp = getcwd(NULL, 0);
	if (!temp)
		ft_error("pwd", shell, 1);
	if (!shell->parsed->next)
	{
		write(STDOUT_FILENO, temp, ft_strlen(temp));
		write(STDOUT_FILENO, "\n", 1);
	}
	free (temp);
}

void	ft_env(t_shell *shell)
{
	t_env	*temp;

	temp = shell->env;
	if (!temp)
		ft_error("ft_env", shell, 1);
	while (temp)
	{
		if (temp->val && temp->key)
			printf("%s\n", temp->str);
		temp = temp->next;
	}
}

void	ft_cd(t_shell *shell)
{
	char	*old_p;
	char	*new_p;
	char	*path;

 	 if (access(".", F_OK) == -1)
    {
        ft_error("Current directory does not exist", shell, 1);
        return;
    }
	old_p = getcwd(NULL, 0);
	if (!old_p)
		ft_error("no old pwd", shell, 1);
	if (!shell->gen->cmd_args[1] || !*shell->gen->cmd_args[1])
		path = ft_get_env(shell->env, "HOME");
	else
		path = ft_strjoin_three(old_p, "/", shell->gen->cmd_args[1]);
	if (!path || !*path)
		path = ft_get_env(shell->env, "HOME");
	if (chdir(path) == -1)
		ft_error("cd", shell, 1);
	new_p = getcwd(NULL, 0);
	if (!new_p)
		ft_error("cd", shell, 1);
	ft_cd_update_env(shell, old_p, new_p);
	free (old_p);
	free (new_p);
	free (path);
}

void	ft_exit(t_shell *shell)
{
	int	status;

	status = 0;
	if (shell->parsed->next)
		printf("exit\n");
	exit(status);
}

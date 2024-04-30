/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_util.c                      	                :+:    :+:            */
/*                                                     +:+                    */
/*   By: atusveld <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/03 15:26:55 by atusveld      #+#    #+#                 */
/*   Updated: 2022/09/07 17:40:34 by atusveld      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
 #include "../../Includes/alex.h"

void	ft_env_add_front(t_env **env, t_env *new) //env list functionality more to come
{
	if (*env && new)
		new->next = *env;
	*env = new;
}

t_env	*ft_new_envtry(char *envp) // iknow its genius
{
	t_env	*new;
	int		i;

	i = 0;
	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		ft_error("envtry malloc error");
	new->next = NULL;
	new->str = NULL;
	new->key = NULL;
	new->val = NULL;
	new->str = strdup(envp);
	while (envp[i] && envp[i] != '=')
		i++;
	new->key = ft_substr(envp, 0, i);
	if (envp[i])
		new->val = ft_strdup(&envp[i + 1]);
	return (new);
}

char	**ft_env_back_to_array(t_env *env) //puts t_env env back to envp ->pointer env array
{
	char	**arr;
	t_env	*temp;
	int		i;

	i = 0;
	temp = env;
	while (temp)
	{
		temp = temp->next;
		i++;
	}
	arr = (char **)malloc((i + 1) *sizeof(char *));
	if (!arr)
		ft_error("back2arr malloc error"); //exit(ENOMEM), refer to error/exit codes;
	arr[i] = NULL;
	i--;
	temp = env;
	while (i >= 0)
	{
		arr[i] = ft_strdup(temp->str);
		temp = temp->next;
		i--;
	}
	return (arr);
}

void	ft_add_envtry(t_env *env, char *key, char *val)
{
	t_env	*new;

	new = ft_find_env(env, key);
	if (new && val)
	{
		free (new->val);
		free (new->str);
		new->val = ft_strdup(val);
		new->str = ft_strjoin_three(key, "=", val);
	}
}

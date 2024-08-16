/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_lst.c                      	                :+:    :+:            */
/*                                                     +:+                    */
/*   By: atusveld <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/03 15:26:55 by atusveld      #+#    #+#                 */
/*   Updated: 2022/09/07 17:40:34 by atusveld      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

 #include "../../Includes/shell.h"

 t_env	*ft_new_envtry(char *envp)
{
	t_env	*new;
	int		i;

	i = 0;
	new = (t_env *)ft_calloc(1, sizeof(t_env));
	new->str = strdup(envp);
	while (envp[i] && envp[i] != '=')
		i++;
	new->key = ft_substr(envp, 0, i);
	if (envp[i])
		new->val = ft_strdup(&envp[i + 1]);
	if (!new->str || !new->key || !new->val)
		return (NULL);
	return (new);
}



void	ft_add_envtry(t_env *env, char *key, char *val)
{
	t_env	*new;

	new = ft_find_env(env, key);
	if (!new)
		return ;
	if (new && val)
	{
		free (new->val);
		free (new->str);
		new->val = ft_strdup(val);
		new->str = ft_strjoin_three(key, "=", val);
	}
}

void	ft_env_add_front(t_env **env, t_env *new)
{
	if (*env && new)
	{
		new->next = *env;
		*env = new;
	}
	return ;
}

void	ft_del_env(t_env **env, t_env *val)
{
	t_env	*temp;

	temp = *env;
	if (val == temp)
	{
		*env = val->next;
		ft_free_env(&val);
		return ;
	}
	while (temp->next != val)
		temp = temp->next;
	temp->next = val->next;
	ft_free_env(&val);
	return ;
}

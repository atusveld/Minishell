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

 #include "../../Includes/alex.h"

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

void	ft_env_add_front(t_env **env, t_env *new)
{
	if (*env && new)
		new->next = *env;
	*env = new;
}

void	ft_del_env(t_env **env, t_env *temp)
{
	t_env	*ele;

	ele = *env;
	if (temp == ele)
	{
		*env = temp->next;
		ft_free_env(&temp);
		return ;
	}
	while (ele->next != temp)
		ele = ele->next;
	ele->next = temp->next;
	ft_free_env(&temp);
}

void	ft_unset_env(t_env **env, char *key)
{
	t_env	*keyval;

	if (!key)
		return ;
	keyval = ft_find_env(*env, key);
	if (!keyval)
		return ;
	ft_del_env(env, keyval);
}
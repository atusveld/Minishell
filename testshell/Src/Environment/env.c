/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                      	                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: atusveld <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/03 15:26:55 by atusveld      #+#    #+#                 */
/*   Updated: 2022/09/07 17:40:34 by atusveld      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/alex.h"

t_env	*ft_build_env(char **envp) //setup new t_env out of main envp
{
	t_env	*new;

	new = NULL;
	while (*envp)
	{
		ft_env_add_front(&new, ft_new_envtry(*envp));
		envp++;
	}
	return (new);
}

char	*ft_get_env(t_env *env, char *key) //get env values
{
	t_env	*ret;

	ret = ft_find_env(env, key);
	if (!ret)
		return (NULL);
	return (ret->val);
}

t_env	*ft_find_env(t_env *env, char *key) //find key value in env
{
	if (!env || !key)
		return (NULL);
	while (env)
	{
		if (env->key && !ft_strncmp(env->key, key, ft_strlen(key) + 1))
			return (env);
		env = env->next;
	}
	return (NULL);
}

void	ft_free_env(t_env **env)
{
	t_env	*tmp;

	while (*env)
	{
		tmp = (*env)->next;
		ft_free_env_ele(*env);
		*env = tmp;
	}
	return ;
}

void	ft_free_env_ele(t_env *env)
{
	if (env->str)
		free(env->str);
	if (env->key)
		free(env->key);
	if (env->val)
		free(env->val);
	free(env);
	return ;
}

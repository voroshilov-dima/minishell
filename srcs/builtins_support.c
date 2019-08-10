/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_support.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 14:02:40 by dvoroshy          #+#    #+#             */
/*   Updated: 2019/08/10 14:02:41 by dvoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_home_folder(t_dictionary *environment)
{
	while (environment)
	{
		if (ft_strcmp(environment->key, "HOME") == 0)
			return (environment->value);
		environment = environment->next;
	}
	return (NULL);
}

int		is_directory(char *path)
{
	struct stat	meta;

	if (stat(path, &meta) != 0)
		return (0);
	return (S_ISDIR(meta.st_mode));
}

void	ms_setenv_internal(char *key, char *value, t_dictionary **environment)
{
	t_dictionary	*env;

	env = *environment;
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
		{
			env->value = value;
			return ;
		}
		else if (env->next == NULL)
		{
			env->next = dictionary_create(key, value);
			return ;
		}
		env = env->next;
	}
}

char	*ms_getenv(char *name, t_dictionary *env)
{
	while (env)
	{
		if (ft_strcmp(env->key, name) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

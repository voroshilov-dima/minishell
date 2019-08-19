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

int		is_directory(char *path)
{
	struct stat	meta;

	if (stat(path, &meta) != 0)
		return (0);
	return (S_ISDIR(meta.st_mode));
}

char	*get_parent_dir(t_dictionary *env)
{
	int		i;
	int		pos;
	char	*pwd;
	char	*parent;

	i = 0;
	pos = -1;
	pwd = ms_getenv("PWD", env);
	if (!pwd)
		return (NULL);
	if (ft_strcmp(pwd, "/") == 0)
		return (ft_strdup("/"));
	while (pwd[i])
	{
		if (pwd[i] == '/')
			pos = i;
		i++;
	}
	if (pos == 0)
		return (ft_strdup("/"));
	parent = ft_strsub(pwd, 0, pos);
	return (parent);
}

void	update_dir_variables(char *dir, t_dictionary **environment)
{
	char *old_pwd;
	char *pwd;

	old_pwd = ms_getenv("PWD", *environment);
	if (old_pwd)
		ms_setenv_internal("OLDPWD", old_pwd, environment);
	if (ft_strcmp(dir, ".") == 0)
		ms_setenv_internal("PWD", old_pwd, environment);
	else if (ft_strcmp(dir, "..") == 0)
	{
		pwd = get_parent_dir(*environment);
		ms_setenv_internal("PWD", pwd, environment);
		free(pwd);
	}
	else if (dir[0] == '/')
		ms_setenv_internal("PWD", dir, environment);
	else
	{
		pwd = ms_join_paths(*environment, dir);
		ms_setenv_internal("PWD", pwd, environment);
		if (pwd)
			free(pwd);
	}
}

void	ms_setenv_internal(char *key, char *value, t_dictionary **environment)
{
	t_dictionary	*env;

	env = *environment;
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
		{
			free(env->value);
			if (value)
				env->value = ft_strdup(value);
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

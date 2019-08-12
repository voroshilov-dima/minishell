/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 13:21:16 by dvoroshy          #+#    #+#             */
/*   Updated: 2019/08/10 13:21:18 by dvoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_exit(char **args, t_dictionary **environment)
{
	(void)args;
	(void)environment;
	exit(EXIT_SUCCESS);
}

void	ms_unsetenv(char **args, t_dictionary **environment)
{
	char			*name;
	t_dictionary	*head;
	t_dictionary	*prev;

	name = args[1];
	if (name == NULL)
	{
		print_error("unsetenv", NULL, "Too few arguments");
		return ;
	}
	if (environment == NULL)
		return ;
	prev = NULL;
	head = *environment;
	while (head)
	{
		if (ft_strcmp(head->key, name) == 0)
		{
			if (!prev)
				*environment = head->next;
			else
				prev->next = head->next;
			free_dictionary(head);
			return ;
		}
		prev = head;
		head = head->next;
	}
}

void	ms_setenv(char **args, t_dictionary **environment)
{
	char			*key;
	char			*value;

	key = args[1];
	value = args[2];
	if (key == NULL)
	{
		ms_env(args, environment);
		return ;
	}
	ms_setenv_internal(key, value, environment);
}

void	ms_cd(char **args, t_dictionary **environment)
{
	char *dir;
	char *old_pwd;

	dir = args[1];
	if (dir == NULL || ft_strcmp(dir, "~") == 0)
		dir = get_home_folder(*environment);
	if (access(dir, F_OK) == -1)
		print_error("cd", "No such file or directory", dir);
	else if (!is_directory(dir))
		print_error("cd", "Not a directory", dir);
	else if (access(dir, X_OK) == -1)
		print_error("cd", "Permission denied", dir);
	else if (chdir(dir) == 0)
	{
		ms_setenv_internal("PWD", dir, environment);
		old_pwd = ms_getenv("PWD", *environment);
		ms_setenv_internal("OLDPWD", old_pwd, environment);
	}
	else
		print_error("cd", dir, "Something went wrong");
}

void	ms_env(char **args, t_dictionary **environment)
{
	t_dictionary *env;

	(void)args;
	if (!environment)
		return ;
	env = *environment;
	while (env)
	{
		if (env->value)
			ft_printf("%s=%s\n", env->key, env->value);
		else
			ft_printf("%s=\n", env->key);
		env = env->next;
	}
}

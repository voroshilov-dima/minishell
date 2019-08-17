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

void	ms_echo(char **args, t_dictionary **environment)
{
	int	i;

	i = 1;
	(void)environment;
	while (args[i])
	{
		ft_printf("%s", args[i]);
		if (args[i + 1])
			ft_printf(" ");
		i++;
	}
	ft_printf("\n");
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

	dir = args[1];
	if (dir == NULL)
		dir = ms_getenv("HOME", *environment);
	if (dir && ft_strcmp(dir, "-") == 0)
		dir = ms_getenv("OLDPWD", *environment);
	if (dir == NULL)
		print_error("cd", "HOME not set", NULL);
	else if (access(dir, F_OK) == -1)
		print_error("cd", "No such file or directory", dir);
	else if (!is_directory(dir))
		print_error("cd", "Not a directory", dir);
	else if (access(dir, X_OK) == -1)
		print_error("cd", "Permission denied", dir);
	else if (chdir(dir) == 0)
		update_dir_variables(dir, environment);
	else
		print_error("cd", dir, "Something went wrong");
}

void	ms_pwd(char **args, t_dictionary **environment)
{
	t_dictionary *env;

	(void)args;
	env = *environment;
	while (env)
	{
		if (ft_strcmp(env->key, "PWD") == 0)
		{
			ft_printf("%s\n", env->value);
			return ;
		}
		env = env->next;
	}
	ft_printf("PWD not set\n");
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

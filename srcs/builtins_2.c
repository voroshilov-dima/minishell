/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 11:48:57 by dvoroshy          #+#    #+#             */
/*   Updated: 2019/08/19 11:48:58 by dvoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

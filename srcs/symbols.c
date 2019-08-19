/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbols.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 11:23:43 by dvoroshy          #+#    #+#             */
/*   Updated: 2019/08/12 11:23:47 by dvoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*handle_tilde(char *str, t_dictionary *env)
{
	char	*new_str;
	char	*home_dir;
	char	*substr;
	int		len;

	new_str = NULL;
	if (str[0] != '~' || (str[1] != 0 && str[1] != '/'))
		return (str);
	home_dir = ms_getenv("HOME", env);
	if (!home_dir)
		return (NULL);
	if (str[1] == 0)
		new_str = ft_strdup(home_dir);
	else
	{
		len = ft_strlen(str);
		substr = ft_strsub(str, 1, len - 1);
		new_str = ft_strjoin(home_dir, substr);
		free(substr);
	}
	free(str);
	return (new_str);
}

static char	*handle_dollar(char *str, t_dictionary *env)
{
	while (env)
	{
		if (ft_strcmp(env->key, str + 1) == 0)
		{
			free(str);
			return (ft_strdup(env->value));
		}
		env = env->next;
	}
	return (NULL);
}

void		handle_symbols(char **args, t_dictionary *env)
{
	int	i;

	i = 0;
	while (args[i])
	{
		args[i] = handle_tilde(args[i], env);
		if (args[i] && args[i][0] == '$' && args[i][1])
			args[i] = handle_dollar(args[i], env);
		i++;
	}
}

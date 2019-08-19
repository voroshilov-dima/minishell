/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 13:21:25 by dvoroshy          #+#    #+#             */
/*   Updated: 2019/08/10 13:21:26 by dvoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_dictionary	*parse_environ(void)
{
	extern char		**environ;
	t_dictionary	*environment;
	int				i;

	i = 0;
	if (environ == NULL || environ[i] == NULL)
		return (NULL);
	environment = string_to_dictionary(environ[i++]);
	while (environ[i])
	{
		dictionary_append(environment, string_to_dictionary(environ[i]));
		i++;
	}
	return (environment);
}

static char		*concat(char *key, char *value)
{
	char	*str;
	int		key_len;
	int		value_len;
	int		i;

	key_len = ft_strlen(key);
	value_len = (value ? ft_strlen(value) : 0);
	str = (char *)malloc(sizeof(char) * (key_len + value_len + 2));
	i = 0;
	while (i < key_len)
	{
		str[i] = key[i];
		i++;
	}
	str[i] = '=';
	i = 0;
	while (i < value_len)
	{
		str[key_len + 1 + i] = value[i];
		i++;
	}
	str[key_len + value_len + 1] = 0;
	return (str);
}

char			**list_to_array(t_dictionary *environment)
{
	t_dictionary	*pointer;
	char			**env;
	int				len;
	int				i;

	if (!environment)
		return (NULL);
	len = 0;
	pointer = environment;
	while (pointer)
	{
		len++;
		pointer = pointer->next;
	}
	env = (char **)malloc(sizeof(char *) * (len + 1));
	i = 0;
	while (environment)
	{
		env[i] = concat(environment->key, environment->value);
		environment = environment->next;
		i++;
	}
	env[len] = 0;
	return (env);
}

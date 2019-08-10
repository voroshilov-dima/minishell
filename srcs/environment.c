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

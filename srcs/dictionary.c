/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dictionary.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 13:21:21 by dvoroshy          #+#    #+#             */
/*   Updated: 2019/08/10 13:21:23 by dvoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_dictionary	*dictionary_create(char *key, char *value)
{
	t_dictionary	*dict;

	dict = (t_dictionary *)malloc(sizeof(t_dictionary));
	dict->key = ft_strdup(key);
	dict->value = ft_strdup(value);
	dict->next = NULL;
	return (dict);
}

t_dictionary	*string_to_dictionary(char *str)
{
	t_dictionary	*dict;
	int				len;
	int				equal_sign_pos;
	char			*key;
	char			*value;

	len = ft_strlen(str);
	equal_sign_pos = 0;
	while (str[equal_sign_pos] != '=')
		equal_sign_pos++;
	key = ft_strsub(str, 0, equal_sign_pos);
	value = ft_strsub(str, equal_sign_pos + 1, len);
	if (ft_strcmp(key, "HOME") == 0)
		g_home = ft_strdup(value);
	dict = dictionary_create(key, value);
	free(key);
	free(value);
	return (dict);
}

void			dictionary_append(t_dictionary *main, t_dictionary *new)
{
	while (main->next)
		main = main->next;
	main->next = new;
}

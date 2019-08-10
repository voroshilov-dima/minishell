/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 13:21:41 by dvoroshy          #+#    #+#             */
/*   Updated: 2019/08/10 13:21:42 by dvoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**get_path(t_dictionary *environment)
{
	char *path_string;
	char **path;

	path_string = NULL;
	while (environment)
	{
		if (ft_strcmp(environment->key, "PATH") == 0)
			path_string = environment->value;
		environment = environment->next;
	}
	if (!path_string)
		return (NULL);
	path = ft_strsplit(path_string, ':');
	return (path);
}

static char	*get_full_path(char *dir, char *file)
{
	char	*dir_with_slash;
	char	*file_path;

	if (dir == NULL)
		return (ft_strdup(file));
	if (dir[ft_strlen(dir) - 1] == '/')
		dir_with_slash = ft_strdup(dir);
	else
		dir_with_slash = ft_strjoin(dir, "/");
	file_path = ft_strjoin(dir_with_slash, file);
	free(dir_with_slash);
	return (file_path);
}

char		*find_program_path(char *name, t_dictionary *env)
{
	char			**path;
	struct dirent	*dirent;
	DIR				*dir;
	int				i;

	i = 0;
	path = get_path(env);
	while (path[i])
	{
		dir = opendir(path[i]);
		while ((dirent = readdir(dir)) != NULL)
		{
			if (ft_strcmp(dirent->d_name, name) == 0)
				return (get_full_path(path[i], dirent->d_name));
		}
		i++;
	}
	return (NULL);
}

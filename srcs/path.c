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

char		*find_file_in_directory(char *dir_name, char *file_name)
{
	DIR				*dir;
	struct dirent	*dirent;
	char			*full_path;

	full_path = NULL;
	dir = opendir(dir_name);
	while ((dirent = readdir(dir)) != NULL)
	{
		if (ft_strcmp(dirent->d_name, file_name) == 0)
		{
			full_path = get_full_path(dir_name, dirent->d_name);
			break ;
		}
	}
	closedir(dir);
	return (full_path);
}

char		*find_program_path(char *name, t_dictionary *env)
{
	char	**path;
	char	*full_path;
	int		i;

	i = 0;
	full_path = NULL;
	path = get_path(env);
	while (path[i])
	{
		full_path = find_file_in_directory(path[i], name);
		if (full_path)
			break ;
		i++;
	}
	free_table(path);
	return (full_path);
}

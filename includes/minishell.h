/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 13:21:53 by dvoroshy          #+#    #+#             */
/*   Updated: 2019/08/10 13:21:54 by dvoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <dirent.h>
# include <stdio.h>

# define BUFSIZE 1024
# define TRUE 1
# define FALSE 0

typedef struct	s_dictionary
{
	char				*key;
	char				*value;
	struct s_dictionary	*next;
}				t_dictionary;

typedef struct	s_builtin
{
	char *name;
	void (*func)(char **, t_dictionary **);
}				t_builtin;

char			*g_home;

void			minishell_loop(t_dictionary **environment);

char			*readline(void);
t_dictionary	*parse_environ(void);
char			**list_to_array(t_dictionary *environment);
char			*find_program_path(char *name, t_dictionary *env);

void			ms_cd(char **args, t_dictionary **environment);
void			ms_env(char **args, t_dictionary **environment);
void			ms_setenv(char **args, t_dictionary **environment);
void			ms_unsetenv(char **args, t_dictionary **environment);
void			ms_echo(char **args, t_dictionary **environment);
void			ms_pwd(char **args, t_dictionary **environment);
void			ms_exit(char **args, t_dictionary **environment);

void			ms_setenv_internal(char *key, char *value,
					t_dictionary **environment);
char			*ms_getenv(char *name, t_dictionary *env);
int				is_directory(char *path);
void			update_dir_variables(char *dir, t_dictionary **environment);

t_dictionary	*string_to_dictionary(char *str);
t_dictionary	*dictionary_create(char *key, char *value);
void			dictionary_append(t_dictionary *main, t_dictionary *new);

void			handle_symbols(char **args, t_dictionary *env);

void			free_table(char **table);
void			free_dictionary(t_dictionary *dict);

void			throw_error(char *command, char *error_message);
void			print_error(char *command, char *arg, char *error_message);

#endif

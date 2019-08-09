#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <dirent.h>
# include <stdio.h>

# define BUFSIZE 1024
# define TRUE 1
# define FALSE 0

extern char **environ;

typedef struct	s_dictionary
{
	char				*key;
	char				*value;
	struct s_dictionary	*next;
}				t_dictionary;

typedef struct	s_builtin
{
	char *name;
	void (*func)(char **, t_dictionary *);
}				t_builtin;

char			*readline(void);
void			throw_error(char *command, char *error_message);
void			print_error(char *command, char *arg, char *error_message);
void			ms_env(char **args, t_dictionary *environment);
void			ms_cd(char **args, t_dictionary *environment);
void			ms_exit(char **args, t_dictionary *environment);
t_dictionary	*string_to_dictionary(char *str);
void			dictionary_append(t_dictionary *main, t_dictionary *new);
t_dictionary	*parse_environ(void);
void			minishell_loop(t_dictionary *environment);
char			*find_program_path(char *name, t_dictionary *environment);

#endif

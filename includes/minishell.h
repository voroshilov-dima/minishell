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
	int (*func)(char **, t_dictionary *);
}				t_builtin;

char	*readline(void);
int		ms_env(char **args, t_dictionary *environment);
int		ms_cd(char **args, t_dictionary *environment);
int		ms_exit(char **args, t_dictionary *environment);

#endif

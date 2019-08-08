#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>

# define BUFSIZE 1024

extern char **environ;

typedef struct	s_builtin
{
	char *name;
	int (*func)(char **);
}				t_builtin;

typedef struct	s_dictionary
{
	char				*key;
	char				*value;
	struct s_dictionary	*next;
}				t_dictionary;

char	*readline(void);
int		cd(char **args);
int		env(char **args);

#endif

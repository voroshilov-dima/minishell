#include "minishell.h"

static char	*get_home_folder(t_dictionary *environment)
{
	while (environment)
	{
		if (ft_strcmp(environment->key, "HOME") == 0) // case?
			return (environment->value);
		environment = environment->next;
	}
	return (NULL);
}

int ms_exit(char **args, t_dictionary *environment)
{
	(void)args;
	(void)environment;

	exit(EXIT_SUCCESS);
}

int ms_cd(char **args, t_dictionary *environment)
{
	char *dir;

	dir = args[1];
  	if (dir == NULL || ft_strcmp(dir, "~") == 0)
		dir = get_home_folder(environment);
	if (chdir(dir) != 0)
    	perror("minishell");
  	return (1);
}

int	ms_env(char **args, t_dictionary *environment)
{
	(void)args;
	while (environment)
	{
		printf("%s=%s\n", environment->key, environment->value);
		environment = environment->next;
	}
	return (1);
}
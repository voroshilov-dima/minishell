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

static int	is_directory(char *path)
{
   struct stat meta;
   if (stat(path, &meta) != 0)
       return 0;
   return S_ISDIR(meta.st_mode);
}

void	ms_exit(char **args, t_dictionary *environment)
{
	(void)args;
	(void)environment;

	exit(EXIT_SUCCESS);
}



void	ms_cd(char **args, t_dictionary *environment)
{
	char *dir;

	dir = args[1];
  	if (dir == NULL || ft_strcmp(dir, "~") == 0)
		dir = get_home_folder(environment);
	if (access(dir, F_OK) == -1)
		print_error("cd", dir, "No such file or directory");
	else if (access(dir, X_OK) == -1)
		print_error("cd", dir, "Permission denied");
	else if (!is_directory(dir))
		print_error("cd", dir, "Not a directory");
	else if (chdir(dir) != 0)
	{
		// set PWD
	}
	else
		print_error("cd", dir, "Something went wrong");
}

void	ms_env(char **args, t_dictionary *environment)
{
	(void)args;
	while (environment)
	{
		ft_printf("%s=%s\n", environment->key, environment->value);
		environment = environment->next;
	}
}
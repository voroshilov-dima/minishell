#include "minishell.h"



char	**get_path(t_dictionary *environment)
{
	char *path_string;
	char **path;

	path_string = NULL;
	while (environment)
	{
		if (ft_strcmp(environment->key, "PATH") == 0) // should be case senitive?
			path_string = environment->value;
		environment = environment->next;
	}
	if (!path_string)
		return (NULL);
	path = ft_strsplit(path_string, ':');
	return (path);
}

char    *get_full_path(char *dir, char *file)
{
    char *dir_with_slash;
    char *file_path;

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

char	*find_program_path(char *name, t_dictionary *environment)
{
	char			**path;
	struct dirent	*dirent;
	DIR				*dir;
	int				i;

	i = 0;
	path = get_path(environment); // clear memory allocated
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

int launch(char **args, t_dictionary *environment)
{
	(void)args;	

	pid_t	pid, wpid;
	int		status;
	char	*program;

	pid = fork();
	if (pid == 0)
	{
    	// Child process
		program = find_program_path(args[0], environment);
		if (!program)
		{
			printf("%s: command not found\n", args[0]);
			exit(EXIT_FAILURE);
		}
    	if (!program || execve(program, args, environ) == -1)
		{
      		exit(EXIT_FAILURE);
    	}
    	
  	}
	else if (pid < 0)
	{
    	// Error forking
    	perror("minishell");
  	}
	else
	{
		// Parent process
		do {
		wpid = waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }

  return 1;
}

int		execute(char **args, t_dictionary *environment)
{
	static t_builtin builtins[] = {
		{"cd", ms_cd},
		{"env", ms_env},
		{"exit", ms_exit},
		{"null", NULL}
	};

	int	i;
	if (args[0] == NULL)
		return (1);
	
	i = 0;
	while (builtins[i].func != NULL)
	{
		if (ft_strcmp(builtins[i].name, args[0]) == 0)
      		return (builtins[i].func(args, environment));
		i++;
	}
	return launch(args, environment);
}

void	minishell_loop(t_dictionary *environment)
{
	char	*line;
  	char	**args;

	while (TRUE)
	{
		printf("$> ");
		line = readline();
    	args = ft_strsplit(line, ' ');
    	execute(args, environment);
	}
}

t_dictionary *string_to_dictionary(char *str)
{
	t_dictionary	*dict;
	int				len;
	int				equal_sign_pos;
	

	if ((dict = (t_dictionary *)malloc(sizeof(t_dictionary))))
	{
		equal_sign_pos = 0;
		while (str[equal_sign_pos] != '=')
			equal_sign_pos++;
		len = ft_strlen(str);
		dict->key = ft_strsub(str, 0, equal_sign_pos);
		dict->value = ft_strsub(str, equal_sign_pos + 1, len);
		dict->next = NULL;
		return (dict);
	}
	else
		return (NULL);
}

void			append(t_dictionary *main, t_dictionary *new)
{
	while (main->next)
		main = main->next;
	main->next = new;
}

t_dictionary	*parse_environ(void)
{
	t_dictionary *environment;
	int i;
	
	i = 0;
	if (environ == NULL || environ[i] == NULL)
		return (NULL);
	environment = string_to_dictionary(environ[i]);
	i++;
	while (environ[i])
	{
		append(environment, string_to_dictionary(environ[i]));
		i++;
	}
	return (environment);
}



int main (int argc, char *argv[])
{
	(void)argc;
	(void)argv;
	t_dictionary *environment; 

	environment = parse_environ();
	
	minishell_loop(environment);
	// Perform any shutdown/cleanup.

	return (1);
}
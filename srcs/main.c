#include "minishell.h"




// char	*find_program_path(char *program)
// {
// 	int	i;

// 	i = 0;
// 	while (ft_strncmp(PA)
// }

int launch(char **args)
{
	(void)args;	

	/*
	pid_t	pid, wpid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
    	// Child process
    	if (execve(args[0], args, environ) == -1)
		{
      		perror("sh");
    	}
    	exit(EXIT_FAILURE);
  	}
	else if (pid < 0)
	{
    	// Error forking
    	perror("lsh");
  	}
	else
	{
		// Parent process
		do {
		wpid = waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }
  */

  return 1;
}

int		execute(char **args)
{
	static t_builtin builtins[] = {
		{"cd", cd},
		{"env", env},
		{"null", NULL}
	};

	int	i;
	if (args[0] == NULL)
		return (1);
	
	i = 0;
	while (builtins[i].func != NULL)
	{
		if (ft_strcmp(builtins[i].name, args[0]) == 0)
      		return (builtins[i].func(args));
		i++;
	}
	return launch(args);
}

void	minishell_loop(void)
{
	char	*line;
  	char	**args;
  	int		status;

	status = 1;
	while (status)
	{
		printf("$> ");
		line = readline();
    	args = ft_strsplit(line, ' ');
    	status = execute(args);
	}
}

// while (environ[i] != 0)
// 	{
// 		printf("%s\n", environ[i]);
// 		i++;
// 	}

char	*get_key(char *str)
{
	int	i;

	i = 0;
	while (str && *str != '=')
		

}

char	*get_value(char *str)
{

}

t_dictionary *parse_environ(void)
{
	t_dictionary *env;
	int i;
	char *key;
	char *value;
	
	i = 0;
	if (environ == NULL || environ[0] == NULL)
		return (NULL);

	list_new(get_key(environ[0]), get_value(environ[1]));
	
	while (environ[i])
	{

	}
}


int main (int argc, char *argv[])
{
	(void)argc;
	(void)argv;
	int	i;
	t_dictionary *env; 

	env = parse_environ();
	i = 0;

	

	// Load config files, if any.
	minishell_loop();
	// Perform any shutdown/cleanup.

	return 1;
}
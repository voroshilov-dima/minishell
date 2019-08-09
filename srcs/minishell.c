#include "minishell.h"

void	launch(char **args, t_dictionary *environment)
{
	(void)args;	

	pid_t	pid, wpid;
	int		status;
	char	*program;

	pid = fork();
	if (pid < 0)
    	throw_error("fork", "forking failed");
	if (pid == 0)
	{
    	// Child process
		program = find_program_path(args[0], environment);
		if (!program)
			throw_error(args[0], "command not found");
		execve(program, args, environ);
      	throw_error(args[0], "Permission denied");
  	}
	else
	{
		// Parent process
		do {
		wpid = waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
  	}
}

void		execute(char **args, t_dictionary *environment)
{
	int	i;
	static t_builtin builtins[] = {
		{"cd", ms_cd},
		{"env", ms_env},
		{"exit", ms_exit},
		{"null", NULL}
	};

	if (!args || args[0] == NULL)
		return ;
	i = 0;
	while (builtins[i].func != NULL)
	{
		if (ft_strcmp(builtins[i].name, args[0]) == 0)
		{
			builtins[i].func(args, environment);
			return ;
		}
		i++;
	}
	launch(args, environment);
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
#include "minishell.h"

int cd(char **args)
{
	char *dir;

	dir = args[1];
  	if (dir == NULL)
		chdir("~");		  
	else if (chdir(dir) != 0)
    	perror("minishell");
  	return (1);
}

int	env(char **args)
{
	int	i;
	
	(void)args;
	i = 0;
	while (environ[i])
	{
		ft_printf("%s\n", environ[i]);
		i++;
	}
	return (1);
}
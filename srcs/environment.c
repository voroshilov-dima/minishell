#include "minishell.h"

t_dictionary	*parse_environ(void)
{
	t_dictionary	*environment;
	int				i;
	
	i = 0;
	if (environ == NULL || environ[i] == NULL)
		return (NULL);
	environment = string_to_dictionary(environ[i++]);
	while (environ[i])
	{
		dictionary_append(environment, string_to_dictionary(environ[i]));
		i++;
	}
	return (environment);
}

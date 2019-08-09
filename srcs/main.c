#include "minishell.h"

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
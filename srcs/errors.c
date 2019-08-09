#include "minishell.h"

void	throw_error(char *command, char *error_message)
{
	ft_printf("minishell: %s: %s\n", command, error_message);
	exit(EXIT_FAILURE);
}

void	print_error(char *command, char *arg, char *error_message)
{
	ft_printf("minishell: %s: %s: %s\n", command, arg, error_message);
}
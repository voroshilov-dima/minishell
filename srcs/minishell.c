/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 13:21:37 by dvoroshy          #+#    #+#             */
/*   Updated: 2019/08/10 13:21:38 by dvoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_builtin	g_builtins[] = {
	{"cd", ms_cd},
	{"env", ms_env},
	{"setenv", ms_setenv},
	{"unsetenv", ms_unsetenv},
	{"exit", ms_exit},
	{"null", NULL}
};



void				launch(char **args, t_dictionary *environment)
{
	pid_t	pid;
	pid_t	wpid;
	int		status;
	char	*program;

	(void)args;
	pid = fork();
	if (pid < 0)
		throw_error("fork", "forking failed");
	if (pid == 0)
	{
		program = find_program_path(args[0], environment);
		if (!program)
			throw_error(args[0], "command not found");
		execve(program, args, NULL);
		throw_error(args[0], "Permission denied");
	}
	else
	{
		wpid = waitpid(pid, &status, WUNTRACED);
		ft_printf("Done\n");
		// } while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
}

void				execute(char **args, t_dictionary **environment)
{
	int	i;

	if (!args || args[0] == NULL)
		return ;
	i = 0;
	while (g_builtins[i].func != NULL)
	{
		if (ft_strcmp(g_builtins[i].name, args[0]) == 0)
		{
			g_builtins[i].func(args, environment);
			return ;
		}
		i++;
	}
	launch(args, *environment);
}



void				minishell_loop(t_dictionary **environment)
{
	char	*line;
	char	**args;

	
	while (TRUE)
	{
		
		ft_printf("$> ");
		line = readline();
		args = ft_strsplit(line, ' ');
		execute(args, environment);
	}
}

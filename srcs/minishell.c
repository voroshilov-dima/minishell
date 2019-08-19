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
	{"echo", ms_echo},
	{"pwd", ms_pwd},
	{"exit", ms_exit},
	{"null", NULL}
};

static void			handle_sigint(int sig)
{
	(void)sig;
	ft_printf("\n");
}

void				print_table(char **env)
{
	int i;

	i = 0;
	while (env[i])
	{
		ft_printf("%s\n", env[i]);
		i++;
	}
}

void				launch(char **args, t_dictionary *env)
{
	pid_t	pid;
	int		status;
	char	*program;
	char	**env_array;

	(void)args;
	pid = fork();
	if (pid < 0)
		throw_error("fork", "forking failed");
	if (pid == 0)
	{
		program = find_program_path(args[0], env);
		if (!program)
			throw_error(args[0], "command not found");
		env_array = list_to_array(env);
		execve(program, args, NULL);
		free(program);
		free_table(env_array);
		throw_error(args[0], "Permission denied");
	}
	else
	{
		signal(SIGINT, handle_sigint);
		waitpid(pid, &status, WUNTRACED);
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
		if (line)
		{
			args = ft_strsplit(line, ' ');
			free(line);
			handle_symbols(args, *environment);
			execute(args, environment);
			free_table(args);
		}
	}
}

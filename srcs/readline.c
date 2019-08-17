/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 13:21:45 by dvoroshy          #+#    #+#             */
/*   Updated: 2019/08/10 13:21:46 by dvoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int			g_position;
static int			g_buff_size;

static void			handle_sigint(int sig) 
{
	(void)sig;
	g_position = 0;
	ft_printf("\n$> ");
}

static void			quit_minishell(void)
{
	ft_printf("\n");
	free(g_home);
	exit(EXIT_SUCCESS);
}

static char			*move_position(char *buffer)
{
	char *new_buffer;

	g_position++;
	if (g_position >= g_buff_size)
	{
		new_buffer = malloc(sizeof(char) * (g_buff_size + BUFSIZE));
		ft_memcpy(new_buffer, buffer, g_buff_size);
		g_buff_size += BUFSIZE;
		free(buffer);
		return (new_buffer);
	}
	else
		return (buffer);
}

char	*readline(void)
{
	char	*buffer;
	char	c;

	g_position = 0;
	g_buff_size = BUFSIZE;
	buffer = malloc(sizeof(char) * g_buff_size);
	signal(SIGINT, handle_sigint);
	while (TRUE)
	{
		if (!read(0, &c, 1))
		{
	 		if (g_position == 0)
				quit_minishell();
			continue;
		}
		if (c == '\n' || c == EOF)
		{
			buffer[g_position] = '\0';
			return (buffer);
		}
		else
			buffer[g_position] = c;
		buffer = move_position(buffer);
	}
	return (NULL);
}

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

static int			position;
static int			buff_size;

static void			handle_sigint(int sig) 
{
	(void)sig;
	position = 0;
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

	position++;
	if (position >= buff_size)
	{
		new_buffer = malloc(sizeof(char) * (buff_size + BUFSIZE));
		ft_memcpy(new_buffer, buffer, buff_size);
		buff_size += BUFSIZE;
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

	position = 0;
	buff_size = BUFSIZE;
	buffer = malloc(sizeof(char) * buff_size);
	signal(SIGINT, handle_sigint);
	while (TRUE)
	{
		if (!read(0, &c, 1))
		{
	 		if (position == 0)
				quit_minishell();
			continue;
		}
		if (c == '\n' || c == EOF)
		{
			buffer[position] = '\0';
			return (buffer);
		}
		else
			buffer[position] = c;
		buffer = move_position(buffer);
	}
	return (NULL);
}

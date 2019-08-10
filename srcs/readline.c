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

int			g_keep_reading = TRUE;

void				handle_sigint(int sig) 
{
	(void)sig;
	ft_printf("I'm here\n");
	g_keep_reading = FALSE;
	//exit(EXIT_SUCCESS);

} 

char	*readline(void)
{
	int		bufsize;
	int		position;
	char	*buffer;
	char	c;
	int		readed;

	bufsize = BUFSIZE;
	position = 0;
	buffer = malloc(sizeof(char) * bufsize);
	signal(SIGINT, handle_sigint);
	while (TRUE)
	{
		readed = read(0, &c, 1);
		if (!readed)
		{
	 		if (position == 0)
			{
				ft_printf("\n");
				exit(EXIT_SUCCESS);
			}
				
			continue;
		}
		if (c == '\n' || c == EOF)
		{
			buffer[position] = '\0';
			return (buffer);
		}
		else
			buffer[position] = c;
		position++;
		if (position >= bufsize)
		{
			bufsize += BUFSIZE;
			buffer = realloc(buffer, bufsize);
		}
	}
	ft_printf("OUT\n");
	return (NULL);
}

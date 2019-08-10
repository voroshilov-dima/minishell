/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 13:21:33 by dvoroshy          #+#    #+#             */
/*   Updated: 2019/08/10 13:21:34 by dvoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[])
{
	t_dictionary *environment;

	(void)argc;
	(void)argv;
	
	environment = parse_environ();
	minishell_loop(&environment);
	return (1);
}

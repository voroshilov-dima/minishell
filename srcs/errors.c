/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 13:21:29 by dvoroshy          #+#    #+#             */
/*   Updated: 2019/08/10 13:21:30 by dvoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	throw_error(char *command, char *error_message)
{
	ft_printf("minishell: %s: %s\n", command, error_message);
	exit(EXIT_FAILURE);
}

void	print_error(char *command, char *arg, char *error_message)
{
	if (arg)
		ft_printf("minishell: %s: %s: %s\n", command, arg, error_message);
	else
		ft_printf("minishell: %s: %s\n", command, error_message);
}

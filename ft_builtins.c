/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brjorgen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 06:09:32 by brjorgen          #+#    #+#             */
/*   Updated: 2019/11/16 06:09:43 by brjorgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_builtin_names[__BUILTIN_NUMBER] = {
	STRINGIFY(ft_cd),
	STRINGIFY(ft_echo),
	STRINGIFY(ft_help),
};

bool	(*ft_builtin_functions[__BUILTIN_NUMBER])(char **) = {
	&ft_cd,
	&ft_echo,
	&ft_help
};

bool	ft_cd(char *dir)
{	
	if (chdir(dir) != 0)
	{
		return (false);
	}
	return (true);
}

bool	ft_echo(char *str)
{
	ft_putstr_fd(str, 1);
	return (true);
}

bool	ft_help(void)
{
	unsigned short i;

	i = 0;
	ft_putstr("Minishell: the (very) basic terminal emulator.\n");
	ft_putstr("Usage: [Unimaginative Prompt] : [COMMAND] [ARGUMENTS]\n");
	ft_putstr("builtins:\n");
	while (i < __BUILTIN_NUMBER)
	{
		ft_putstr("\t->");
		ft_putstr(ft_builtin_names[i]);
		ft_putchar('\n');
		i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brjorgen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 06:09:32 by brjorgen          #+#    #+#             */
/*   Updated: 2019/11/18 17:02:35 by brjorgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*builtin_names[BUILTIN_NUMBER] = {
	"cd",
	"echo",
	"help",
	"clear"
};

bool	(*ft_builtin_function[BUILTIN_NUMBER])(char **) = {
	&ft_cd,
	&ft_echo,
	&ft_help,
	&ft_clear
};

bool	ft_exec_builtins(char **command)
{
	unsigned int i;

	i = 0;
	while (i < BUILTIN_NUMBER)
	{
		if (ft_strcmp(builtin_names[i], command[0]) == 0)
			return ((*ft_builtin_function[i])(command));		
		i++;
	}
	return (false);
}

bool	ft_cd(char **dir)
{
	if (chdir(dir[1]) != 0)
	{
		return (false);
	}
	return (true);
}

bool	ft_echo(char **str)
{
	ft_putendl_fd(str[1], 1);
	return (true);
}

bool	ft_clear(__attribute__((unused)) char **param)
{
	short	i;
	char	buff[125];

	i = 0;
	while (i < 125)
	{
		buff[i] = '\n';
		i++;
	}
	buff[i] = '\0';
	ft_putstr(buff);
	return (true);
}

bool	ft_help(__attribute__((unused)) char **param)
{
	unsigned short i;

	i = 0;
	ft_putstr("Minishell: the (very) basic terminal emulator.\n");
	ft_putstr("Usage: [Unimaginative Prompt] : [COMMAND] [ARGUMENTS]\n");
	ft_putstr("builtins:\n");
	while (i < BUILTIN_NUMBER)
	{
		ft_putstr("\t->");
		ft_putstr(builtin_names[i]);
		ft_putchar('\n');
		i++;
	}
	return (true);
}

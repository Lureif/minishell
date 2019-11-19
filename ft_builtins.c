/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brjorgen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 06:09:32 by brjorgen          #+#    #+#             */
/*   Updated: 2019/11/19 06:06:01 by brjorgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*builtin_names[BUILTIN_NUMBER] = {
	"cd",
	"echo",
	"help",
	"clear",
};

char	*env_builtin_names[ENV_BUILTIN_NUMBER] = {
	"env",
	"setenv",
	"unsetenv",
	"exit",
};

bool	(*ft_env_builtin_function[ENV_BUILTIN_NUMBER])(t_sh_utils *) = {
	&ft_env,
	&ft_setenv,
	&ft_unsetenv,
	&ft_exit,
};

bool	(*ft_builtin_function[BUILTIN_NUMBER])(char **) = {
	&ft_cd,
	&ft_echo,
	&ft_help,
	&ft_clear,
};

bool	ft_exec_builtins(t_sh_utils *sh_utils)
{
	unsigned int i;

	i = 0;
	while (i < BUILTIN_NUMBER)
	{
		if (ft_strcmp(builtin_names[i], sh_utils->command[0]) == 0)
			return ((*ft_builtin_function[i])(sh_utils->command));
		i++;
	}
	i = 0;
	while (i < ENV_BUILTIN_NUMBER)
	{
		if (ft_strcmp(env_builtin_names[i], sh_utils->command[0]) == 0)
			return ((*ft_env_builtin_function[i])(sh_utils));
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
	unsigned int i;
	
	i = 1;
	while (str[i])
	{
		ft_putstr_fd(str[i], 1);
		if (str[i] + 1)
			ft_putchar_fd(' ', 1);
		i++;
	}
	ft_putchar('\n');
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

bool	ft_env(t_sh_utils *sh_utils)
{
	unsigned int i;

	i = 0;
	while (sh_utils->envp[0][i])
	{
        ft_putendl(sh_utils->envp[0][i]);
		i++;
	}
	return (true);
}

bool	ft_setenv(t_sh_utils *sh_utils)
{
	unsigned int index;
	unsigned int i;

	i = 0;
	index = ret_env_var_index(*sh_utils->envp, sh_utils->command[1], 0);
	if (index)
	{
		while (sh_utils->envp[0][index][i] != '=')
			i++;
		i++;
		ft_bzero(sh_utils->envp[0][index] + i, ft_strlen(sh_utils->envp[0][index]) - i);
		if (sh_utils->command[2])
			ft_strcpy(sh_utils->envp[0][index] + i, sh_utils->command[2]);		
	}
	return (true);
}

bool	ft_unsetenv(t_sh_utils *sh_utils)
{
	if (sh_utils->command[2])
		ft_bzero(sh_utils->command[2], sizeof(sh_utils->command[2]));
	else
		ft_setenv(sh_utils);
	return (true);
}

bool	ft_help(__attribute__((unused)) char **param)
{
	unsigned short i;

	i = 0;
	ft_print_welcome_banner();
	ft_putstr("Minishell: the (very) basic terminal emulator.\n");
	ft_putstr("Usage: [Unimaginative Prompt] : [COMMAND] [ARGUMENTS]\n");
	ft_putstr("builtins:\n");
	while (i < BUILTIN_NUMBER)
	{
		ft_putstr("\t->");
		if (builtin_names[i])
			ft_putstr(builtin_names[i]);
		ft_putchar('\n');
		i++;
	}
	return (true);
}

bool	ft_exit(t_sh_utils *sh_utils)
{
	ft_cleanup(&*sh_utils->line, &sh_utils->command);
	exit(EXIT_SUCCESS);
}

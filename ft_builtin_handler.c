/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_handler.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brjorgen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 10:55:35 by brjorgen          #+#    #+#             */
/*   Updated: 2019/12/05 23:20:53 by brjorgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

const char	*g_builtin_names[BUILTIN_NUMBER] = {
	"echo",
	"help",
	"clear",
};

const char	*g_env_builtin_names[ENV_BUILTIN_NUMBER] = {
	"cd",
	"env",
	"setenv",
	"unsetenv",
	"exit",
};

bool	(*g_ft_env_builtin_function[ENV_BUILTIN_NUMBER])(t_sh_utils *) = {
	&ft_cd,
	&ft_env,
	&ft_setenv,
	&ft_unsetenv,
	&ft_exit,
};

bool	(*g_ft_builtin_function[BUILTIN_NUMBER])(char **) = {
	&ft_echo,
	&ft_help,
	&ft_clear,
};

bool	ft_exec_builtins(t_sh_utils *sh_utils)
{
	unsigned int i;

	i = 0;
	if (!sh_utils->command || !*sh_utils->command)
		return (false);
	while (i < BUILTIN_NUMBER)
	{
		if (ft_strcmp(g_builtin_names[i], sh_utils->command[0]) == 0)
			return ((*g_ft_builtin_function[i])(sh_utils->command));
		i++;
	}
	i = 0;
	while (i < ENV_BUILTIN_NUMBER)
	{
		if (ft_strcmp(g_env_builtin_names[i], sh_utils->command[0]) == 0)
			return ((*g_ft_env_builtin_function[i])(sh_utils));
		i++;
	}
	return (false);
}

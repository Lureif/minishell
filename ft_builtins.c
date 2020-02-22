/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brjorgen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 06:09:32 by brjorgen          #+#    #+#             */
/*   Updated: 2019/12/10 04:10:32 by brjorgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_cd(t_sh_utils *sh_utils)
{
	int		i;

	if (tab_size((const void **)sh_utils->command) == 1)
	{
		i = ret_env_var_index(sh_utils->envp[0], "HOME", 0);
		chdir(sh_utils->envp[0][i] + ft_strlen("HOME="));
	}
	else if (*sh_utils->command[1] == '-')
	{
		chdir(sh_utils->prev_working_dir);
		ft_cd_print_dir_switch(sh_utils, true);
	}
	else if (chdir(sh_utils->command[1]) != 0)
	{
		error_handler("cd", no_such_dir_file);
		return (true);
	}
	else
		ft_cd_print_dir_switch(sh_utils, false);
	ft_cd_update_prev_dir(sh_utils);
	return (true);
}

bool	ft_echo(char **str)
{
	unsigned int i;

	i = 1;
	if (!*str)
		return (false);
	while (str[i])
	{
		ft_putstr_fd(str[i], 1);
		ft_putchar_fd(' ', 1);
		i++;
	}
	ft_putchar('\n');
	return (true);
}

bool	ft_clear(char **param)
{
	(void)param;
	ft_putstr(CLEAR_SCREEN);
	return (true);
}

void	ft_print_names(void)
{
	unsigned short	i;
	extern char		*g_builtin_names[BUILTIN_NUMBER];
	extern char		*g_env_builtin_names[ENV_BUILTIN_NUMBER];

	i = 0;
	while (i < BUILTIN_NUMBER)
	{
		ft_putstr("\t->");
		if (g_builtin_names[i])
			ft_putstr(g_builtin_names[i]);
		ft_putchar('\n');
		i++;
	}
	i = 0;
	while (i < ENV_BUILTIN_NUMBER)
	{
		ft_putstr("\t->");
		if (g_env_builtin_names[i])
			ft_putstr(g_env_builtin_names[i]);
		ft_putchar('\n');
		i++;
	}
}

bool	ft_help(char **param)
{
	(void)param;
	ft_print_welcome_banner();
	ft_putstr("Minishell: the (very) basic terminal emulator.\n");
	ft_putstr("Usage: [Unimaginative Prompt] : [COMMAND] [ARGUMENTS]\n");
	ft_putstr("builtins:\n");
	ft_print_names();
	return (true);
}

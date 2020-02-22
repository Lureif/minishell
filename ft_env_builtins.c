/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brjorgen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 14:00:50 by brjorgen          #+#    #+#             */
/*   Updated: 2019/12/14 03:15:13 by brjorgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	HEADER	   : minishell.h
**	PROJ  	   : minishell
**	NAME  	   : ft_setenv
**	ARGS  	   : -> sh_utils : structure contianing all critical data
**	DESCRIPTION:
**	either edits an entry in envp or adds one, depending on what is contained
**	within the command and weather or not this already exists within the envp.
*/

bool	ft_setenv(t_sh_utils *sh_utils)
{
	int				index;
	unsigned int	i;

	i = 0;
	if (!*sh_utils->envp || !sh_utils->command)
		return (false);
	index = ret_env_var_index(*sh_utils->envp, sh_utils->command[1], 0);
	if (index > -1)
	{
		while (sh_utils->envp[0][index][i] != '=')
			i++;
		i++;
		ft_bzero(sh_utils->envp[0][index] + i,
				ft_strlen(sh_utils->envp[0][index]) - i);
		if (sh_utils->command[2])
			ft_strcpy(sh_utils->envp[0][index] + i, sh_utils->command[2]);
	}
	else
	{
		if (ft_check_input_add_var(sh_utils) == false)
			error_handler("setenv", no_such_var);
	}
	return (true);
}

/*
**	HEADER	   : minishell.h
**	PROJ  	   : minishell
**	NAME  	   : ft_unsetenv
**	ARGS  	   : -> sh_utils : structure contianing all critical data
**	DESCRIPTION:
**	deletes an element from an allocated 2d array.
*/

bool	ft_unsetenv(t_sh_utils *sh_utils)
{
	if (!sh_utils->command || !sh_utils->command[1])
	{
		error_handler("unsetenv", no_args_passed);
		return (true);
	}
	else
	{
		*sh_utils->envp = ft_str_tab_del_element(*sh_utils->envp
												, sh_utils->command[1]);
	}
	return (true);
}

/*
**	HEADER	   : minishell.h
**	PROJ  	   : minishell
**	NAME  	   : ft_env
**	ARGS  	   : -> sh_utils : structure contianing all critical data
**	DESCRIPTION:
**	prints the environement variables (all entries in envp).
*/

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

/*
**	HEADER	   : minishell.h
**	PROJ  	   : minishell
**	NAME  	   : ft_exit
**	ARGS  	   : -> sh_utils : structure contianing all critical data
**	DESCRIPTION:
**	coerces ft_cleanup and exit to free all allocated memory within sh_utils
**	and exits the minishell process.
*/

bool	ft_exit(t_sh_utils *sh_utils)
{
	ft_cleanup(sh_utils);
	free_tab((void **)*sh_utils->envp);
	free(sh_utils->prev_working_dir);
	free(sh_utils->cur_working_dir);
	exit(EXIT_SUCCESS);
}

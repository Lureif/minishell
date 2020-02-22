/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_launch.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brjorgen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 18:14:23 by brjorgen          #+#    #+#             */
/*   Updated: 2019/12/14 03:19:17 by brjorgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>
#include <dirent.h>

/*
**	HEADER	   : minishell.h
**	PROJ  	   : minishell
**	ARGS       : -> PATH environement variable string (without "PATH=")
**	      	     -> address of args (split input line) (NOTE: *args[0]
**	       		is wanted executable)
**	      	     -> address of envp, the environement variables.
**	DESCRIPTION:
**	This function's aim is to run a process.
**	it first checks if any of its params are NULL,
**	then creates a child process with fork().
**	if the child process was created correctly, the bin_path is
**	split by its ':' separator and the result stored in bin_paths
**	which we iterate over (and join to a '/' and the *args[0]
**	on every iteration) untill find the correct path for the
**	executable, which will cause execve to run the process in the
**	child. The path which was formatted with a / and exec
**	name is freed after every iteration.
**	Should the PID not be created correctly, Waitpid is called
**	in the parent process.
*/

bool	dirp(char *pathname)
{
	int fd;

	fd = open(pathname, O_DIRECTORY);
	if (fd != -1)
	{
		close(fd);
		return (true);
	}
	return (false);
}

bool	dumb_check_v2(char *args, int initial)
{
	if (args[initial] == '\0')
		return (true);
	else if (args[initial] == '.'
			|| args[initial] == '/'
			|| ft_strcmp(args + initial, "./") == 0)
		return (dumb_check_v2(args, initial + 1));
	else
		return (false);
}

bool	ft_process_launch(char ***args, char ***envp)
{
	char			*p_t_e;
	bool			p_c;

	if (!args || !*args || !envp || !*envp)
		return (false);
	p_c = ft_path_function(&p_t_e, args, envp);
	if (**args && dumb_check_v2(**args, 0) == true)
	{
		if (p_t_e && *p_t_e && !!p_c)
			free(p_t_e);
		return (false);
	}
	if ((!*envp || p_c == false || p_t_e == NULL)
		&& !parse_arg(**args) && !parse_arg(p_t_e))
	{
		if (p_t_e != NULL)
			error_handler("(internal) process_launcher", undefined_path);
		else if (**args && !parse_arg(**args))
			error_handler(**args, command_not_found);
		return (false);
	}
	if ((**args && p_c && p_t_e) || (parse_arg(**args) && !dirp(**args)))
		ft_fork_actions(args, envp, p_t_e);
	free(p_t_e);
	return (true);
}

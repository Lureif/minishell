/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_launch.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brjorgen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 18:14:23 by brjorgen          #+#    #+#             */
/*   Updated: 2019/11/19 05:28:46 by brjorgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*error_codes[ERROR_CODE_NUMBER] = {
	": Command not found.\n",
};

void	error_handler(char *process_name, int error_code)
{
	ft_putstr_fd(process_name, 1);
	ft_putstr_fd(error_codes[error_code], 1);
}

bool	ft_parse_process_name(char **args)
{
	if (**args == '.' || **args == '/')
		return (true);
	return (false);
}

bool	ft_process_launch_path(char ***args, char ***envp)
{
	if (access(*args[0], R_OK) != -1)
	{
		execve(*args[0], *args, *envp);
		return (true);
	}
	else
	{
//		error_handler(*args[0], 0);
		return (false);
	}
	return (true);
}

bool	ft_check_process_is_path(char ***args, char ***envp)
{
	if (ft_parse_process_name(*args) == true)
	{
		if (ft_process_launch_path(args, envp) == true)
		{
			return (true);
		}
		else
		{
			return (false);
		}
	}
	return (false);
}

bool	ft_process_launch(char *bin_paths, char ***args, char ***envp)
{
	unsigned int	i;
	char			**split_bin_paths;
	char			*path;
	int				status;    
	pid_t			pid;

	i = 0;
	if (!bin_paths || !*args || !*envp)
	{
		return (false);
	}
	pid = fork();
	split_bin_paths = NULL;
	if (pid == 0)
	{
		if ((status = ft_check_process_is_path(args, envp)) == true)
			return (true);
		split_bin_paths = ft_strsplit(bin_paths, ':');
		while (split_bin_paths[i])
		{			
			path = ft_strjoin(split_bin_paths[i], "/");
			path = ft_strjoin(path, **args);
			if (access(path, R_OK) == -1)
			{
				i++;
			}
			else
			{
				execve(path, *args, *envp);
			}
			free(path);
			if ((int)i == tab_size((const void **)split_bin_paths))
			{
				error_handler(**args, 0);
				break ;
			}
		}
	}
	else
	{
		waitpid(pid, &status, WUNTRACED);
	}
	return (true);
}

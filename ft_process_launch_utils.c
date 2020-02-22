/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_launch_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brjorgen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 01:48:23 by brjorgen          #+#    #+#             */
/*   Updated: 2019/12/14 03:20:17 by brjorgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_child_process_handler(char ***args, char ***envp, char *path_to_exec)
{
	if (parse_arg(args[0][0]) == true && path_to_exec == NULL)
		ft_child_process(**args, *args, *envp);
	else
		ft_child_process(path_to_exec, *args, *envp);
	return (true);
}

bool	ft_child_process(char *bin_path, char **args, char **envp)
{
	if (access(bin_path, X_OK) == -1 && access(*args, X_OK) == -1)
	{
		if (*args)
			error_handler(*args, command_not_found);
		exit(EXIT_FAILURE);
	}
	if (execve(bin_path, args, envp) == -1 && execve(*args, args, envp) == -1)
	{
		error_handler("(internal) process_launcher", could_not_execute);
		exit(EXIT_FAILURE);
	}
	return (true);
}

bool	ft_fork_actions(char ***args, char ***envp, char *path_to_exec)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
		ft_child_process_handler(args, envp, path_to_exec);
	else if (pid > 0)
		waitpid(pid, &status, WUNTRACED);
	else
		error_handler("(internal) process_launcher", could_not_execute);
	return (true);
}

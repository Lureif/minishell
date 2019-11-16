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

bool	ft_process_launch(char *bin_paths, char ***args, char ***envp)
{
	char 		**split_bin_paths;
	char		*path;
	unsigned int 	i;
	int		status;
	pid_t		pid;

	i = 0;
	if (!bin_paths || !*args || !*envp)
		return (false);
	pid = fork();
	if (pid == 0)
	{
		split_bin_paths = ft_strsplit(bin_paths, ':');
		while (split_bin_paths[i])
		{
			path = ft_strjoin(split_bin_paths[i], "/");
			path = ft_strjoin(path, **args);
			if (execve(path, *args, *envp) == -1)
			{
				i++;
			}
			free(path);
		}
	}
	else
	{
		waitpid(pid, &status, WUNTRACED);
	}
	return (true);
}

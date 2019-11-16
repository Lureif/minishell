/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brjorgen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 03:41:29 by brjorgen          #+#    #+#             */
/*   Updated: 2019/11/16 06:16:49 by brjorgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "get_next_line.h"

void	ft_print_prompt(void)
{
	ft_putstr_fd(SH_PROMPT, 1);
}

void	free_tab(void **tab)
{
	unsigned int y;

	y = 0;
	while (tab[y])
	{
		free(tab[y]);
		y++;
	}
	free(tab);
}

void	ft_cleanup_shell(char *path, char *input_line, char **split_input_line)
{
	if (path)
		free(path);
	if (input_line)
		free(input_line);
	if (split_input_line)
		free_tab((void **)split_input_line);
}

unsigned int		tab_size(const void **tab)
{
	unsigned int i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

bool	ft_process_launch(char *bin_paths, char ***args, char ***envp)
{
	char 	**split_bin_paths;
	char	*path;
	unsigned int 	i;
	int		status;
	pid_t	pid;

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

int		main(__attribute__((unused)) int ac, __attribute__((unused)) char **av, char **envp)
{
	int index;
	char *line;
	char **input;

	index = ret_env_var_index(envp, "PATH", 0);
	ret_env_var(&envp[index], ft_strlen("PATH"));
	av++;
	while (420)
	{
		ft_print_prompt();
		get_next_line(1, &line);
		input = ft_strsplit(line, ' ');
		ft_process_launch(envp[index], &input, &envp);
		free_tab((void **) input);
		free(line);
	}    
}

/* bool	ft_process_launch(char *path, char **args, char ***envp) */
/* { */
	
/* 	int		status; */
/* 	_Bool	caused_error; */
/* 	pid_t	child_pid; */
/* 	pid_t	wait_pid; */
/* 	char	**bin_path; */
	
/* 	child_pid = fork(); */
/* 	if (child_pid < 0) */
/* 	{ */
/* 		perror("\nminishell"); */
/* 	} */
/* 	bin_path = ft_strsplit(path, ':'); */
/* 	while (bin_path && *bin_path) */
/* 	{ */
/* 		if (child_pid == 0) */
/* 		{ */
/* 			if (execve(*bin_path, args, *envp) == -1) */
/* 			{ */
/* 				perror("\nminishell"); */
/* 			} */
/* 			exit(EXIT_SUCCESS); */
/* 		} */
/* 		else */
/* 		{ */
/* 			wait_pid = waitpid(child_pid, &status, WUNTRACED); */
/* 		} */
/* 		bin_path++; */
/* 	} */
/* 	return (true); */
/* } */

/* int	main(__attribute__((unused)) int ac, __attribute__((unused)) char **av, char **envp) */
/* { */
/* 	char			**split_input_line; */
/* 	char			*input_line; */
/* //	char			*path; */
/* 	unsigned int 	index; */

/* 	index = ret_env_var_index(envp, "PATH", 0); */
/* 	ret_env_var(&envp[index], ft_strlen("PATH") + 1); */
/* 	while (420) */
/* 	{ */
/* 		ft_print_prompt(); */
/* 		get_next_line(1, &input_line); */
/* 		split_input_line = ft_strsplit(input_line, ' '); */
/* 		if (split_input_line && split_input_line[0]) */
/* 		{ */
/* 			if (!(ft_process_launch(envp[index], &split_input_line, &envp))) */
/* 			{ */
/* 				printf("failed pathetically.\n"); */
/* //				ft_cleanup_shell(path, input_line, split_input_line); */
/* 				exit(EXIT_FAILURE); */
/* 			} */
/* 		} */
/* //		ft_cleanup_shell(path, input_line, split_input_line); */
/* 	} */
/* 	return (0); */
/* } */

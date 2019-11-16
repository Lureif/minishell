/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trying_execve.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brjorgen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 03:42:57 by brjorgen          #+#    #+#             */
/*   Updated: 2019/11/16 06:04:56 by brjorgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		main(__attribute__((unused)) int ac, char **av, char **envp)
{
	int error;
	int 	index;
    char 	*path;
	char	**BIN_PATH;

	index = ret_env_var_index(envp, "PATH", 0);
	ret_env_var(&envp[index], ft_strlen("PATH"));
    BIN_PATH = ft_strsplit(envp[index], ':');
	index = 0;

	pid_t pid;
	pid = fork();
	while (BIN_PATH[index])
	{
		path = ft_strjoin(BIN_PATH[index], "/");
		path = ft_strjoin(path, av[1]);
//		printf("%s\n", path);
		error = execve(path, av + 1, envp);
		if (error == -1)
		{
			index++;
		}
		else
			exit(EXIT_SUCCESS);
		/* else */
		/* 	exit(EXIT_SUCCESS); */
		/* index++; */
		/* free(path); */
		/* printf("================================================\n"); */
	}
	ft_putchar('\n');
	return (0);
}

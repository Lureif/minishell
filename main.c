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

int	tab_size(const void **tab)
{
	unsigned int i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

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

void		ft_cleanup(char **line, char ***tab)
{
	free(*line);
	free_tab((void **)*tab);
}

int		main(__attribute__((unused)) int ac, __attribute__((unused)) char **av, char **envp)
{
	int	index;
	char	*line;
	char	**input;

	index = ret_env_var_index(envp, "PATH", 0);
	ret_env_var(&envp[index], ft_strlen("PATH"));
	while (420)
	{
		ft_print_prompt();
		get_next_line(1, &line);
		input = ft_strsplit(line, ' ');
		ft_exec_builtins(input);
		ft_process_launch(envp[index], &input, &envp);
		ft_cleanup(&line, &input);
	}
}

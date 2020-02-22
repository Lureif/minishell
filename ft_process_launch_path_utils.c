/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_launch_path_utils.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brjorgen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 01:50:01 by brjorgen          #+#    #+#             */
/*   Updated: 2019/12/14 03:18:00 by brjorgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	parse_arg(char *args)
{
	char	tab[3];

	if (!args)
		return (false);
	ft_bzero(tab, 2);
	tab[0] = *args;
	tab[1] = *args + 1;
	if ((ft_strcmp(tab, "./") == 0 || tab[0] == '/')
		&& access(args, R_OK) != -1 && ft_strlen(args) > 3)
		return (true);
	return (false);
}

char	*ft_check_access(char **split_bin_paths, char *arg)
{
	unsigned int	i;
	char			*tmp;
	char			*path;

	i = 0;
	if (!arg || !split_bin_paths)
		return (NULL);
	while (split_bin_paths[i])
	{
		if (i == 0)
			tmp = ft_strjoin(split_bin_paths[i] + ft_strlen("PATH="), "/");
		else
			tmp = ft_strjoin(split_bin_paths[i], "/");
		path = ft_strjoin(tmp, arg);
		free(tmp);
		if (access(path, R_OK) == -1)
		{
			free(path);
			i++;
		}
		else
			return (path);
	}
	return (NULL);
}

bool	ft_path_check_stat(char **path_to_exec, char ***args)
{
	if (path_to_exec == NULL)
	{
		if (!**args || !*path_to_exec)
		{
			error_handler(**args, command_not_found);
		}
		return (false);
	}
	return (true);
}

bool	ft_path_function(char **path_to_exec, char ***args, char ***envp)
{
	int		index;
	char	**split_bin_paths;

	index = ret_env_var_index(*envp, "PATH", 0);
	if (index == -1)
	{
		*path_to_exec = NULL;
		return (false);
	}
	split_bin_paths = ft_strsplit(envp[0][index], ':');
	*path_to_exec = ft_check_access(split_bin_paths, **args);
	if (split_bin_paths && *split_bin_paths)
		free_tab((void **)split_bin_paths);
	if (path_to_exec == NULL)
		return (false);
	return (true);
}

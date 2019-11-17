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

int		main(__attribute__((unused)) int ac, __attribute__((unused)) char **av, char **envp)
{
	int	index;
	char	*line;
	char	**input;

	index = ret_env_var_index(envp, "PATH", 0);
	trim_env_var(&envp[index]);
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

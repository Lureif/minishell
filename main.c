/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brjorgen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 03:41:29 by brjorgen          #+#    #+#             */
/*   Updated: 2019/11/19 06:05:26 by brjorgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "get_next_line.h"

int		main(__attribute__((unused)) int ac, __attribute__((unused)) char **av, char **envp)
{
	t_sh_utils sh_utils;
	int		index;
	char	*line;
	char	**input;

    
	ft_print_welcome_banner();
	index = ret_env_var_index(envp, "PATH", 0);
	trim_env_var(&envp[index]);    
	while (420)
	{
		ft_print_prompt();
		get_next_line(1, &line);
		input = ft_strsplit(line, ' ');
		sh_utils.envp = &envp;
		sh_utils.command = input;
		sh_utils.line = &line;
		if (ft_exec_builtins(&sh_utils) == false)
			ft_process_launch(envp[index], &input, &envp);
		ft_cleanup(&line, &input);
	}
}

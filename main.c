/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brjorgen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 03:41:29 by brjorgen          #+#    #+#             */
/*   Updated: 2019/12/14 02:04:34 by brjorgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "get_next_line.h"

void	ft_clean_str(char *line)
{
	unsigned int i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\t')
			line[i] = ' ';
		i++;
	}
}

void	ft_fill_struct(t_sh_utils *sh_utils, char **line, char ***envp)
{
	char		**input;
	static bool	swish = false;

	input = ft_strsplit(*line, ' ');
	if (!*input)
		ft_strdel(input);
	if (envp)
	{
		ft_parse_input(input, *envp);
		sh_utils->envp = envp;
	}
	sh_utils->line = line;
	sh_utils->command = input;
	if (swish == false)
	{
		ft_cd_update_prev_dir(sh_utils);
		swish = true;
	}
}

int		main(int ac, char **av, char **envp)
{
	t_sh_utils	sh_utils;
	char		*line;

	(void)ac;
	(void)av;
	ft_print_welcome_banner();
	if (envp)
		envp = ft_str_tab_cpy(envp);
	while (420)
	{
		ft_print_prompt();
		get_next_line(0, &line);
		if (line == NULL)
			exit(EXIT_SUCCESS);
		ft_clean_str(line);
		ft_fill_struct(&sh_utils, &line, &envp);
		if (ft_exec_builtins(&sh_utils) == false)
			ft_process_launch(&sh_utils.command, sh_utils.envp);
		ft_cleanup(&sh_utils);
	}
}

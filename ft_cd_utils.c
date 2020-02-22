/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brjorgen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 02:45:38 by brjorgen          #+#    #+#             */
/*   Updated: 2019/12/07 19:30:36 by brjorgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd_update_prev_dir(t_sh_utils *sh_utils)
{
	char		buff[MAXPATHLEN];
	static bool i = false;

	ft_bzero(buff, MAXPATHLEN);
	getcwd(buff, MAXPATHLEN);
	if (i == false)
	{
		sh_utils->cur_working_dir = ft_strdup(buff);
		sh_utils->prev_working_dir = ft_strdup(buff);
		i = true;
	}
	else
	{
		free(sh_utils->prev_working_dir);
		sh_utils->prev_working_dir = ft_strdup(sh_utils->cur_working_dir);
		free(sh_utils->cur_working_dir);
		sh_utils->cur_working_dir = ft_strdup(buff);
	}
}

void	ft_cd_print_dir_switch(t_sh_utils *sh_utils, bool went_back)
{
	ft_putstr_fd("Switched to dir -> ", 1);
	if (!went_back)
		ft_putstr_fd(sh_utils->command[1], 1);
	else
		ft_putstr_fd(sh_utils->prev_working_dir, 1);
	ft_putchar_fd('\n', 1);
}

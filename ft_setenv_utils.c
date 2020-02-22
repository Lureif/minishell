/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brjorgen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 08:47:18 by brjorgen          #+#    #+#             */
/*   Updated: 2019/12/04 14:21:07 by brjorgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_add_var(char **tab, char *key, char *val)
{
	int end_index;

	end_index = tab_size((const void **)tab);
	tab[end_index] = ft_memalloc(ft_strlen(key) + ft_strlen(val) + 2);
	ft_strcpy(tab[end_index], key);
	ft_strcpy(tab[end_index] + ft_strlen(key), "=");
	ft_strcpy(tab[end_index] + ft_strlen(key) + 1, val);
	tab[end_index + 1] = NULL;
}

bool	ft_check_input_add_var(t_sh_utils *sh_utils)
{
	if (sh_utils->command && sh_utils->command[1] && sh_utils->command[2])
	{
		ft_add_var(*sh_utils->envp, sh_utils->command[1], sh_utils->command[2]);
		sh_utils->changed_env = true;
		return (true);
	}
	return (false);
}

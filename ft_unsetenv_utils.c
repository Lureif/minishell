/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brjorgen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 14:43:00 by brjorgen          #+#    #+#             */
/*   Updated: 2019/12/10 03:49:10 by brjorgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_ret_tab_cpy(char **tab, int to_del_index)
{
	char	**tab_cpy;
	int		i;
	int		y;

	i = 0;
	y = 0;
	tab_cpy = (char **)malloc((sizeof(char *)
							* (tab_size((const void **)tab) * 2)));
	while (tab[i])
	{
		if (i != to_del_index)
		{
			tab_cpy[y] = ft_strdup(tab[i]);
			y++;
		}
		i++;
	}
	tab_cpy[y] = NULL;
	return (tab_cpy);
}

char	**ft_str_tab_del_element(char **tab, char *element)
{
	char	**tab_cpy;
	int		to_del_index;

	if (!element)
	{
		error_handler("(internal) env_del_element", no_args_passed);
		return (tab);
	}
	to_del_index = ret_env_var_index(tab, element, 0);
	if (to_del_index == -1)
	{
		error_handler("(internal) env_del_element", no_such_var);
		return (tab);
	}
	tab_cpy = ft_ret_tab_cpy(tab, to_del_index);
	free_tab((void **)tab);
	return (tab_cpy);
}

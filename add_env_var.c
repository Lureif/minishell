/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_env_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brjorgen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 20:34:21 by brjorgen          #+#    #+#             */
/*   Updated: 2019/12/03 09:46:06 by brjorgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	HEADER	   : minishell.h
**	PROJ  	   : minishell
**	NAME  	   : ft_add_var_in_end_slot
**	ARGS  	   : -> tab_cpy : the tab to which we finished copying the args in
**							  envp
**				 -> key : the new key to add in the environement
**				 -> val : the value to be assigned to key.
**	DESCRIPTION:
**	adds the new environement variable to the end of the newly copied envp tab.
*/

bool	ft_add_var_in_end_slot(char **tab_cpy, char *key, char *val
							, int tab_pos)
{
	char	*new_env_var;
	int		key_len;
	int		val_len;

	key_len = ft_strlen(key);
	val_len = ft_strlen(val);
	key = ft_strjoin(key, "=");
	new_env_var = ft_strjoin(key, val);
	tab_cpy[tab_pos] = (char *)malloc(sizeof(char) * (val_len + key_len) + 1);
	if (!tab_cpy[tab_pos])
		return (false);
	ft_bzero(tab_cpy[tab_pos], val_len + key_len + 1);
	ft_strcpy(tab_cpy[tab_pos], new_env_var);
	free(key);
	free(new_env_var);
	return (true);
}

/*
**	HEADER	   : minishell.h
**	PROJ  	   : minishell
**	NAME  	   : ft_add_env_var
**	ARGS  	   : -> tab : envp
**				 -> key : the new key to be entered in ENV
**				 -> val : the value for the newly created key
**	DESCRIPTION:
**	Adds an environement variable  by creating a copy of envp in memory
**	and adding an extra memory slot at the end of it.
*/

char	**ft_add_env_var(char **tab, char *key, char *val)
{
	char	**tab_cpy;
	int		tab_len;
	int		i;

	if (!(tab_cpy = (char **)malloc(sizeof(char *)
									* ((tab_size((const void **)tab)) + 2))))
		return (NULL);
	i = 0;
	while (tab[i])
	{
		tab_len = ft_strlen(tab[i]);
		if (!(tab_cpy[i] = (char *)malloc(sizeof(char) * (tab_len + 1))))
			return (NULL);
		ft_strcpy(tab_cpy[i], tab[i]);
		i++;
	}
	ft_add_var_in_end_slot(tab_cpy, key, val, i);
	tab_cpy[++i] = NULL;
	return (tab_cpy);
}

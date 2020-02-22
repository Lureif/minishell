/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expantions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brjorgen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 03:18:01 by brjorgen          #+#    #+#             */
/*   Updated: 2019/12/05 23:24:38 by brjorgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	HEADER	   : minishell.h
**	PROJ  	   : minishell
**	NAME  	   : dollar_expantion
**	ARGS  	   : -> to_expand : the string coming after the dollar symbol.
**				 -> envp : the 2d array containing environement variables.
**	DESCRIPTION:
**	expands whatever comes after the dollar symbol.
*/

char	*dollar_expantion(char *to_expand, char **envp)
{
	int index;

	index = ret_env_var_index(envp, to_expand, 0);
	if (index != -1)
	{
		to_expand = ft_strdup(envp[index] + ft_strlen(to_expand - 1));
	}
	else
	{
		error_handler("$", no_such_var);
		return (NULL);
	}
	return (to_expand);
}

/*
**	HEADER	   : minishell.h
**	PROJ  	   : minishell
**	NAME  	   : tilde_expantion
**	ARGS  	   : -> to_expand : the ~.
**				 -> envp : the 2d array containing environement variables.
**	DESCRIPTION:
**	expands the tilde to the HOME variable.
*/

void	tilde_expantion_addon(char **to_expand, char **envp)
{
	char	tmp[125];
	int		index;

	ft_bzero(tmp, 125);
	index = ret_env_var_index(envp, "HOME", 0);
	ft_strcpy(tmp, envp[index] + ft_strlen("HOME="));
	ft_strcpy(tmp + ft_strlen(tmp), "/");
	ft_strcpy(tmp + ft_strlen(tmp), *to_expand + 1);
	*to_expand = ft_strdup(tmp);
}

char	*tilde_expantion(char *to_expand, char **envp)
{
	char	*real_deal;
	int		index;

	index = ret_env_var_index(envp, "HOME", 0);
	real_deal = NULL;
	if (index != -1)
	{
		if (ft_strlen(to_expand) > 1)
		{
			tilde_expantion_addon(&to_expand, envp);
			return (to_expand);
		}
		else
			to_expand = ft_strdup(envp[index] + ft_strlen("HOME="));
	}
	else
	{
		error_handler("~", no_such_var);
		return ("");
	}
	return (to_expand);
}

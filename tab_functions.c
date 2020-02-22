/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brjorgen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 18:20:56 by brjorgen          #+#    #+#             */
/*   Updated: 2019/12/10 00:22:36 by brjorgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	HEADER	   : minishell.h
**	PROJ  	   : minishell
**	NAME  	   : free_tab
**	ARGS  	   : -> 2d array
**	DESCRIPTION:
**	Frees a previously allocated two-dimentional array.
*/

void	free_tab(void **tab)
{
	void			**cpy;

	cpy = tab;
	while (*tab)
	{
		free(*tab);
		*tab = NULL;
		tab++;
	}
	free(cpy);
	cpy = NULL;
}

/*
**	HEADER	   : minishell.h
**	PROJ  	   : minishell
**	NAME  	   : free_tab
**	ARGS  	   : -> 2d array
**	DESCRIPTION:
**	returns size of 2d array.
*/

int		tab_size(const void **tab)
{
	unsigned int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

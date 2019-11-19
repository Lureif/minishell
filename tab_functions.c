/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brjorgen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 18:20:56 by brjorgen          #+#    #+#             */
/*   Updated: 2019/11/18 20:06:10 by brjorgen         ###   ########.fr       */
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
	unsigned int y;

	y = 0;
	while (tab[y])
	{
		free(tab[y]);
		tab[y] = NULL;
		y++;
	}
	free(tab);
}

/*
**	HEADER	   : minishell.h
**	PROJ  	   : minishell
**	NAME  	   : free_tab
**	ARGS  	   : -> 2d array
**	DESCRIPTION:
**	returns size of 2d array.
*/

int tab_size(const void **tab)
{
	unsigned int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

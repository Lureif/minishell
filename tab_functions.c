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
		tab[y] = NULL; // to remove if weird mem errors occur
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

int	tab_size(const void **tab)
{
	unsigned int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

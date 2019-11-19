#include "minishell.h"

/*
**	HEADER	   : minishell.h
**	PROJ  	   : minishell
**	NAME  	   : ft_print_prompt
**	ARGS  	   : none
**	DESCRIPTION:
**	Prints the prompt defined as SH_PROMPT in minishell.h
*/

#define GREE "\x1B[32m"
#define RESET "\033[0m"

void	ft_print_prompt(void)
{
	ft_putstr_fd(GREE, 1);
	ft_putstr_fd(SH_PROMPT, 1);
	ft_putstr_fd(RESET, 1);
}

/*
**	HEADER	   : minishell.h
**	PROJ  	   : minishell
**	NAME  	   : ft_cleanup
**	ARGS  	   : -> address of line
**	      	     -> address of 2D array containing the split
**	DESCRIPTION:
**	Checks the addresses of the arguments and the data
**	contained at these addresses are not null and frees
**	the arguments by coercing free and free_tab
*/

void	ft_cleanup(char **line, char ***tab)
{
	if (line && *line)
		free(*line);
	if (*tab && **tab)
		free_tab((void **)*tab);
}

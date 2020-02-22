/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shell_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brjorgen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 09:30:10 by brjorgen          #+#    #+#             */
/*   Updated: 2019/12/13 04:29:54 by brjorgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

const char	*g_promp_emoji_table[12] = {
	"[ ┬──┬ ノ(ò_óノ) gently~]: ",
	"[ RAGE! (╯°□°)╯︵ ┻━┻	]: ",
	"[ ┻━┻ ︵ ╯(°□° ╯) RAGE!	]: ",
	"[ (づ￣ ³￣)づ  uwuuuu ~]: ",
	"[ (҂◡_◡)ᕤ i await oders	]: ",
	"[ (๑•̀ㅂ•́)ง✧ BRING IT ON	]: ",
	"[ (⊙＿⊙') wtffffffffff	]: ",
	"[ (ಥ﹏ಥ) so sad		]: ",
	"[ ԅ(≖‿≖ԅ) huehuehue	]: ",
	"[ (◕‿◕✿) kawaii shelluru]: ",
	"[ (~‾▿‾)~ we vibiiiin	]: ",
	"[ (￣^￣)ゞ ORDERZ PLZZZ]: "
};

/*
**	HEADER	   : minishell.h
**	PROJ  	   : minishell
**	NAME  	   : ft_print_prompt
**	ARGS  	   : none
**	DESCRIPTION:
**	prints one of prompts in g_prompt_emoji_table using a
**	static iterator.
*/

void	ft_print_prompt(void)
{
	static int i = 0;

	if (i >= 12)
		i = 0;
	ft_putstr_fd(GREE, 1);
	ft_putstr_fd(g_promp_emoji_table[i], 1);
	ft_putstr_fd(RESET, 1);
	i++;
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

void	ft_cleanup(t_sh_utils *sh_utils)
{
	if (sh_utils->line)
		ft_strdel(sh_utils->line);
	if (sh_utils->command)
		free_tab((void **)sh_utils->command);
}

/*
**	HEADER	   : minishell.h
**	PROJ  	   : minishell
**	NAME  	   : ft_str_tab_cpy
**	ARGS  	   : -> tab : 2d array containing envp
**	DESCRIPTION:
**	returns a malloced copy of envp.
*/

char	**ft_str_tab_cpy(char **tab)
{
	static bool swish = false;
	char		**tab_cpy;
	int			size;
	int			i;

	i = 0;
	size = tab_size((const void **)tab);
	if (tab)
		tab_cpy = (char **)malloc((sizeof(char *) * (size * 2)));
	else
		tab_cpy = (char **)malloc(sizeof(char *) * 10);
	ft_bzero(tab_cpy, sizeof(tab_cpy));
	while (tab[i] != NULL)
	{
		tab_cpy[i] = ft_strdup(tab[i]);
		i++;
	}
	tab_cpy[i] = NULL;
	if (swish == true)
		free_tab((void **)tab);
	if (swish == false)
		swish = true;
	return (tab_cpy);
}
